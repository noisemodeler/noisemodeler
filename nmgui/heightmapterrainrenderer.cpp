#include "heightmapterrainrenderer.hpp"

#include <QVector>

#include <sstream>

//TODO remove
#include <iostream>
#include <QDebug>

namespace nmgui {

HeightMapTerrainRenderer::HeightMapTerrainRenderer():
    m_program(),
    m_domain(0,0,1,1),
    m_sourceDirty(true),
    m_generatorFunctionSource("void elevation(in vec2 coords, out float height){height = 0.5;}")
{
}

HeightMapTerrainRenderer::~HeightMapTerrainRenderer()
{
    if (m_program) {
        delete m_program;
        m_program = nullptr;
    }
}

void HeightMapTerrainRenderer::render(){
    glClearColor(1, 1, 0, 1);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    if(!m_program || m_sourceDirty){
        recompileProgram();
    }
    m_program->bind();

    m_program->enableAttributeArray(0);

    float values[] = {
        -10,-10, -5, 1,
         10,-10, -5, 1,
        -10, 10, -5, 1,
         10, 10, -5, 1,
    };
    m_program->setAttributeArray(0, GL_FLOAT, values, 4);

    float l = m_domain.left();
    float t = m_domain.top();
    float w = m_domain.width();
    float h = m_domain.height();
    QVector4D domain{l, t, w, h};
    m_program->setUniformValue("domain", domain);

    //get viewmatrix from camera
    QMatrix4x4 viewMatrix = m_camera.worldToLocalMatrix();
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

//    glDisable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_TEST);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    //unbind everything
    m_program->disableAttributeArray(0);
    m_program->release();
}

void HeightMapTerrainRenderer::recompileProgram()
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
                                       "attribute highp vec4 vertices;\n"
                                       "varying highp vec2 coords;\n"
                                       "void main() {\n"
                                       "    gl_Position = mvp * vertices;\n"
                                       "    coords = vertices.xy*vec2(0.5,0.5)*domain.zw+vec2(0.5,0.5)+domain.xy;\n"
                                       "}\n");
    std::stringstream fs;
    fs << "#version 130\n";

    fs << m_generatorFunctionSource;
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

} // namespace nmgui
