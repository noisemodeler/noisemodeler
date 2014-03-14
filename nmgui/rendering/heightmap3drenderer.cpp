#include "heightmap3drenderer.hpp"

#include <QVector>

#include <sstream>

//TODO remove
#include <iostream>
#include <QDebug>

namespace {

bool lineSegmentIntersectsSphere(QVector3D p1, QVector3D p2, QVector3D sphereCenter, float radius){
    // formula from: http://paulbourke.net/geometry/circlesphere/index.html
    QVector3D &p3 = sphereCenter;
    QVector3D p1p2 = p2-p1;
    const float numerator = QVector3D::dotProduct((p3-p1)*(p1p2),{1,1,1});
    const float denominator = (p1p2).lengthSquared();
    const float u = numerator / denominator;
    if(u<0 || u>1)return false; //line intersection outside line segment
    QVector3D p = p1 + p1p2*u; //intersection point
    QVector3D p3p = p - p3; //vector from center to intersection point
    const float rsquared = radius * radius;
    return p3p.lengthSquared() < rsquared; //checking if closest point on segment is closer to the center than the radius
}

struct TerrainPatchSelection {
    int lodLevel;
    QVector3D position;//lower left corner
    float size;
    void visitChildren(std::function<void(TerrainPatchSelection)> cb){
        cb(TerrainPatchSelection{lodLevel-1, position, size/2});
        cb(TerrainPatchSelection{lodLevel-1, position+QVector3D{1,0,0}*size/2, size/2});
        cb(TerrainPatchSelection{lodLevel-1, position+QVector3D{0,0,-1}*size/2, size/2});
        cb(TerrainPatchSelection{lodLevel-1, position+QVector3D{1,0,-1}*size/2, size/2});
    }
    /** @brief appends appropriate terrainpatches to a list of selections
      * @param ranges the radiuses of different lod ranges
      * @param observerPosition
      * @param selections the collection of selections to draw
      * @return whether the area was covered by this patch or its children
      */
    bool lodSelect(const std::vector<float> &ranges, const QVector3D &observerPosition, std::vector<TerrainPatchSelection> &selections){
        //if this is final lodlevel, or sphere do not intersect, then this is the final lodlevel for this branch of the quad tree
        if(lodLevel==0 || !patchIntersectsSphere(ranges[lodLevel-1], observerPosition)){
            selections.push_back(*this);
            return true;
        }
        visitChildren([&](TerrainPatchSelection patch){
            patch.lodSelect(ranges, observerPosition, selections);
        });
        return true;
    }
    bool patchIntersectsSphere(float radius, QVector3D sphereCenter){
        QVector3D bl = position;
        QVector3D br = bl + QVector3D{1,0, 0}*size; //TODO ideally get height from terrain data here
        QVector3D tl = bl + QVector3D{0,0,-1}*size;
        QVector3D tr = bl + QVector3D{1,0,-1}*size;
        //first check if center is inside
        if(sphereCenter.x()>bl.x() && sphereCenter.x()<br.x() &&
           sphereCenter.z()>bl.z() && sphereCenter.z()<tr.z()){
            return true;
        }
        return lineSegmentIntersectsSphere(bl,br,sphereCenter,radius) ||
               lineSegmentIntersectsSphere(bl,tl,sphereCenter,radius) ||
               lineSegmentIntersectsSphere(br,tr,sphereCenter,radius) ||
               lineSegmentIntersectsSphere(tl,tr,sphereCenter,radius);
    }
};

}

namespace nmgui {

HeightMap3DRenderer::HeightMap3DRenderer():
    m_program(),
    m_state(),
    m_sourceDirty(true)
{
    initialize();
}

HeightMap3DRenderer::~HeightMap3DRenderer()
{
    if (m_program) {
        delete m_program;
        m_program = nullptr;
    }
}

void HeightMap3DRenderer::setState(HeightMap3DExplorer::State &state)
{
    m_sourceDirty |= state.shaderSource!=m_state.shaderSource;
    m_state = state;
}

void HeightMap3DRenderer::render(){
    //select terrain patches of different lod levels here
    //TODO maybe this is not the right place for this kind of code...
    std::vector<TerrainPatchSelection> selections;
    TerrainPatchSelection rootQuad{0,{0,0,0},100};
    rootQuad.lodSelect({10,8,4,2},m_state.camera.position(),selections);



    glClearColor(0.5, 0.7, 1, 1);
    glDepthMask(GL_TRUE);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(!m_program || m_sourceDirty){
        recompileProgram();
    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float l = m_state.domain.left();
    float t = m_state.domain.top();
    float w = m_state.domain.width();
    float h = m_state.domain.height();
    QVector4D domain{l, t, w, h};
    m_program->setUniformValue("domain", domain);


    //get viewmatrix from camera
    QMatrix4x4 viewMatrix = m_state.camera.worldToLocalMatrix();
    QMatrix4x4 modelViewMatrix = viewMatrix * modelMatrix;

    //set up projection matrix
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(65, 1, 1.0, 10024);
//    projectionMatrix.ortho(-10,10,-10,10,0.10,10);
    projectionMatrix.scale({1,-1,1}); //flip Y coordinates because otherwise Qt will render it upside down

    QMatrix4x4 modelMatrix;
    modelMatrix.scale(100);
    modelMatrix.translate(rootQuad.position);
    QMatrix4x4 mvp = projectionMatrix * modelViewMatrix;

    //Pass matrices to shader
    m_program->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_program->setUniformValue("projectionMatrix", projectionMatrix);
    m_program->setUniformValue("mvp", mvp);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glCullFace(GL_BACK);

    //this is where the magic happens
    {
        QOpenGLVertexArrayObject::Binder binder(&m_vao);
        for (int i = 0; i < 1; ++i) {
            glDrawArrays(GL_LINE_STRIP, 0, m_vertexCount);
        }
    }
}

void HeightMap3DRenderer::initialize()
{
    //initialize opengl stuff

    //TODO initialize opengl functions? glewish?
    recompileProgram();
    //prepare textures?
    prepareVertexBuffer();
    prepareVertexArrayObject();
}

void HeightMap3DRenderer::recompileProgram()
{
    if(m_program){
        delete m_program;
        m_program = nullptr;
    }
    m_program = new QOpenGLShaderProgram();
    std::stringstream vs;

    vs << "#version 130\n";
    vs << m_state.shaderSource;
    vs << "uniform vec4 domain;\n"
          "uniform mat4 modelViewMatrix;\n"
          "uniform mat4 projectionMatrix;\n"
          "uniform mat4 mvp;\n"
          "attribute highp vec2 vertices;\n"
          "varying highp vec2 coords;\n"
          "varying vec3 normal;\n"
          "void main() {\n"
          "    coords = vertices.xy*vec2(0.5,0.5)*domain.zw+vec2(0.5,0.5)+domain.xy;\n"
          "    float height;\n"
          "    elevation(coords, height);\n"
          //for now, we'll compute the normals here\n
          "    float rightHeight, forwardHeight;\n"
          //TODO get rid of hard coded delta
          "    float delta = 1.0/64.0;\n"
          "    elevation(vec2(coords.x+delta,coords.y), rightHeight);\n"
          "    elevation(vec2(coords.x,coords.y-delta), forwardHeight);\n"
          //compute normal purely based on these two points (it'll probably look like shit)
          "    vec3 rightVector = normalize(vec3(delta, rightHeight-height, 0));\n"
          "    vec3 forwardVector = normalize(vec3(0, forwardHeight-height, delta));\n"
          "    normal = cross(rightVector, forwardVector);\n"

          "    gl_Position = mvp * vec4(vertices.x,height,vertices.y,1);\n"
          "}\n";

    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vs.str().c_str());
    std::stringstream fs;
    fs << "#version 130\n";

    fs << m_state.shaderSource;
//    fs << "void elevation(in vec2 coords, out float height){height = 0.8+coords.x-mod(coords.y,1);}\n";

    fs << ""
          "uniform mat4 modelViewMatrix;\n"
          "uniform lowp float t;\n"
          "varying highp vec2 coords;\n"
          "varying vec3 normal;\n"
          "void main() {\n"
          "    vec3 n = normalize(modelViewMatrix * vec4(normal,0)).xyz;\n"
          "    vec3 s = normalize(modelViewMatrix * vec4(1,2,1,0)).xyz; //direction towards light source\n"
          "    float height;\n"
          "    elevation(coords, height);\n"
          //material constants
          "    float k_d = 0.7;\n"
          "    float k_height = 0.5;\n"
          //intensities of different types of lighting
          "    float i_d = k_d * max(0, dot(s, n));\n"
          "    float i_height = k_height * height;\n"
          "    float i_total = i_d;// + i_height;\n"
          "    gl_FragColor = vec4(i_total*vec3(1, 1, 1), 1);\n"
//          "    gl_FragColor = vec4(height, height, height, 1);\n"
          "}\n";

    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs.str().c_str());

    m_program->bindAttributeLocation("vertices", 0);
    m_program->link();

    m_sourceDirty = false;
}

void HeightMap3DRenderer::prepareVertexBuffer()
{
    //prepare the data for the buffer
    QVector<QVector2D> vertices;
//    const float tileWidth = 1.0 / static_cast<float>(resolution);
    //column major
//    for (int j=0; j<resolution; ++j) {
//        for(int i=0; i<resolution; ++i){
//        }
//    }
    float dx = 1.f/float(c_resolution);
    float dy = dx;
    for (int y = 0; y < c_resolution-1; ++y) {
        //if not first row, create a degenerate here
        if(y!=0)vertices.append({(c_resolution-1)*dx, y*dx});
        for (int x = c_resolution-1; x >= 0; --x) {
            vertices.append({x*dx,y*dy});
            vertices.append({x*dx,(y+1)*dy});
        }
        if(y!=c_resolution-2)vertices.append({0*dx,(y+1)*dy});
    }
    m_vertexCount = vertices.length();

    //prepare the buffer
    m_gridVerticesBuffer.create();
    m_gridVerticesBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw); //static because the height values will be obtained separately and added in the vertex shader
    m_gridVerticesBuffer.bind();
    m_gridVerticesBuffer.allocate(vertices.data(), m_vertexCount*sizeof(QVector2D)); //second parameter is number of bytes
    m_gridVerticesBuffer.release();
}

void HeightMap3DRenderer::prepareVertexArrayObject()
{
    m_vao.create();
    {
        QOpenGLVertexArrayObject::Binder binder(&m_vao); //automatically release vao when passing out of scope (RAII)
        m_program->bind();
        //bind vertex buffer
        m_gridVerticesBuffer.bind();
        m_program->enableAttributeArray("vertices"); //TODO change "vertices" to something more descriptive
        m_program->setAttributeBuffer("vertices", GL_FLOAT, 0, 2);
    }
}

} // namespace nmgui
