#include "heightmap3drenderer.hpp"

#include <QVector>

#include <sstream>

//TODO remove
#include <iostream>
#include <QDebug>

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
    glClearColor(1, 1, 0, 1);
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
    QMatrix4x4 modelViewMatrix = viewMatrix;

    //set up projection matrix
    QMatrix4x4 projectionMatrix;
    projectionMatrix.perspective(55, 1, 0.1, 128);
//    projectionMatrix.ortho(-10,10,-10,10,0.10,10);

    //precompute model view projection matrix
    QMatrix4x4 mvp = projectionMatrix * modelViewMatrix;

    //Pass matrices to shader
    m_program->setUniformValue("modelViewMatrix", modelViewMatrix);
    m_program->setUniformValue("projectionMatrix", projectionMatrix);
    m_program->setUniformValue("mvp", mvp);

    glEnable(GL_DEPTH_TEST);

    //this is where the magic happens
    {
        QOpenGLVertexArrayObject::Binder binder(&m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, c_resolution*c_resolution);
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

    //set camera to a sensible position and rotation
//    m_camera.setPosition({0,2,0});
//    m_camera.lookAt({0,0,0});
//    m_camera.setOrientation(QQuaternion::fromAxisAndAngle(0,1,0,-90));
}

void HeightMap3DRenderer::recompileProgram()
{
    if(m_program){
        delete m_program;
        m_program = nullptr;
    }
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "#version 130\n"
                                       "uniform vec4 domain;\n"
                                       "uniform mat4 modelViewMatrix;\n"
                                       "uniform mat4 projectionMatrix;\n"
                                       "uniform mat4 mvp;\n"
                                       "attribute highp vec2 vertices;\n"
                                       "varying highp vec2 coords;\n"
                                       "void main() {\n"
                                       "    gl_Position = mvp * vec4(vertices.x,vertices.y,-5,1);\n"
                                       "    coords = vertices.xy*vec2(0.5,0.5)*domain.zw+vec2(0.5,0.5)+domain.xy;\n"
                                       "}\n");
    std::stringstream fs;
    fs << "#version 130\n";

    fs << m_state.shaderSource;
//    fs << "void elevation(in vec2 coords, out float height){height = 0.8+coords.x-mod(coords.y,1);}\n";

    fs << "uniform lowp float t;\n"
          "varying highp vec2 coords;\n"
          "void main() {\n"
          "    float height;\n"
          "    elevation(coords, height);\n"
          "    gl_FragColor = vec4(height, height, height, 1);\n"
          "}\n";

    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fs.str().c_str());

    m_program->bindAttributeLocation("vertices", 0);
    m_program->link();

    m_sourceDirty = false;
}

void HeightMap3DRenderer::prepareVertexBuffer()
{
    //prepare the data for the buffer
    int vertexCount = c_resolution * c_resolution;
    QVector<QVector2D> vertices(vertexCount);
//    const float tileWidth = 1.0 / static_cast<float>(resolution);
    //column major
//    for (int j=0; j<resolution; ++j) {
//        for(int i=0; i<resolution; ++i){
//        }
//    }
    {
        int i=0;//     x,z
        vertices[i++]={1,0}; //bot-right
        vertices[i++]={0,0}; //bot-left
        vertices[i++]={1,1}; //top-right
        vertices[i++]={0,1}; //top-left
    }

    //prepare the buffer
    m_gridVerticesBuffer.create();
    m_gridVerticesBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw); //static because the height values will be obtained separately and added in the vertex shader
    m_gridVerticesBuffer.bind();
    m_gridVerticesBuffer.allocate(vertices.data(), vertexCount*sizeof(QVector2D)); //second parameter is number of bytes
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
