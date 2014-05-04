#include "heightmaptexturerenderer.hpp"

#include <QVector>

#include <sstream>

namespace nmgui {

HeightMapTextureRenderer::HeightMapTextureRenderer():
    m_program(),
    m_state(),
    m_sourceDirty(true),
    m_initialized(false)
{
}

HeightMapTextureRenderer::~HeightMapTextureRenderer()
{
    if (m_program) {
        delete m_program;
        m_program = nullptr;
    }
}

void HeightMapTextureRenderer::setState(HeightMapTextureExplorer::State &state)
{
    m_sourceDirty |= state.shaderSource!=m_state.shaderSource;
    m_state = state;
}

void HeightMapTextureRenderer::render(){
    if(!m_initialized){
        initialize();
    }
    glClearColor(1, 0, 1, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(!m_program || m_sourceDirty){
        recompileProgram();
    }
    m_program->bind();

//    m_program->enableAttributeArray(0); //What does this do again? is it really needed?

    float l = m_state.domain.left();
    float t = m_state.domain.top();
    float w = m_state.domain.width();
    float h = m_state.domain.height();
    QVector4D domain{l, t, w, h};
    m_program->setUniformValue("domain", domain);

    glDisable(GL_DEPTH_TEST);

    //this is where the magic happens
    {
        QOpenGLVertexArrayObject::Binder binder(&m_vao);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4); //four verticess to draw the two triangles
    }

    m_program->release();
}

void HeightMapTextureRenderer::initialize()
{
    //initialize opengl stuff

    //TODO initialize opengl functions? glewish?
    recompileProgram();
    //prepare textures?
    prepareVertexBuffer();
    prepareVertexArrayObject();

    m_initialized = true;
}

void HeightMapTextureRenderer::recompileProgram()
{
    if(m_program){
        delete m_program;
        m_program = nullptr;
    }
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                       "#version 130\n"
                                       "uniform vec4 domain;\n"
                                       "attribute highp vec2 vertices;\n"
                                       "varying highp vec2 coords;\n"
                                       "void main() {\n"
                                       "    gl_Position = vec4(vertices.x,vertices.y,0,1);\n"
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

void HeightMapTextureRenderer::prepareVertexBuffer()
{
    QVector<QVector2D> vertices;
    //                x, y
    vertices.append({-1,-1}); //bot-left
    vertices.append({ 1,-1}); //bot-right
    vertices.append({-1, 1}); //top-left
    vertices.append({ 1, 1}); //top-right

    //prepare the buffer
    m_gridVerticesBuffer.create();
    m_gridVerticesBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw); //static because the height values will be obtained separately and added in the vertex shader
    m_gridVerticesBuffer.bind();
    //TODO size is length?
    m_gridVerticesBuffer.allocate(vertices.data(), vertices.size()*sizeof(QVector2D)); //second parameter is number of bytes
    m_gridVerticesBuffer.release();
}

void HeightMapTextureRenderer::prepareVertexArrayObject()
{
    m_vao.create();
    {
        QOpenGLVertexArrayObject::Binder binder(&m_vao); //automatically release vao when passing out of scope (RAII)
        m_program->bind();
        //bind vertex buffer
        m_gridVerticesBuffer.bind();
        m_program->enableAttributeArray("vertices"); //TODO change "vertices" to something more descriptive
        m_program->setAttributeBuffer("vertices", GL_FLOAT, 0, 2);
        m_gridVerticesBuffer.release();
        m_program->release();
    }
}

} // namespace nmgui
