#include "texturerenderer.hpp"

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>

namespace nmgui {

TextureRenderer::TextureRenderer(QQuickItem *the_parent) :
    QQuickItem(the_parent),
    m_program(0),
    m_t(0),
    m_thread_t(0)
{
    connect(this, SIGNAL(windowChanged(QQuickWindow*)), this, SLOT(handleWindowChanged(QQuickWindow*)));
}

void TextureRenderer::setT(qreal new_t)
{
    if (new_t == m_t)
        return;
    m_t = new_t;
    emit tChanged();
    if (window())
        window()->update();
}

void TextureRenderer::handleWindowChanged(QQuickWindow *win)
{
    //This event is sent when we are first attached to a window
    if(win){
        // Connect the beforeRendering signal to our paint function.
        // Since this call is executed on the rendering thread it must be
        // a Qt::DirectConnection
        connect(win, SIGNAL(afterRendering()), this, SLOT(paint()), Qt::DirectConnection);
        connect(win, SIGNAL(beforeSynchronizing()), this, SLOT(sync()), Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}

void TextureRenderer::paint()
{
        if(!m_program){

            m_program = new QOpenGLShaderProgram();
            m_program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                               "#version 130\n"
                                               "attribute highp vec4 vertices;"
                                               "varying highp vec2 coords;"
                                               "void main() {"
                                               "    gl_Position = vertices;"
                                               "    coords = vertices.xy;"
                                               "}");
            m_program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                               "#version 130\n"
                                               "uniform lowp float t;"
                                               "varying highp vec2 coords;"
                                               "void main() {"
                                               "    lowp float i = 1. - (pow(abs(coords.x), 4.) + pow(abs(coords.y), 4.));"
                                               "    i = smoothstep(t - 0.8, t + 0.8, i);"
                                               "    i = floor(i * 20.) / 20.;"
                                               "    gl_FragColor = vec4(coords * .5 + .5, i, i);"
                                               "}");

            m_program->bindAttributeLocation("vertices", 0);
            m_program->link();

            connect(window()->openglContext(), SIGNAL(aboutToBeDestroyed()),
                    this, SLOT(cleanup()), Qt::DirectConnection);
        }
        m_program->bind();

        m_program->enableAttributeArray(0);

        float values[] = {
                -1, -1,
                1, -1,
                -1, 1,
                1, 1
        };
        m_program->setAttributeArray(0, GL_FLOAT, values, 2);
        m_program->setUniformValue("t", static_cast<float>(m_thread_t));

        auto globalPos = mapToScene(position());
        glViewport(globalPos.x(), window()->height()-height()-globalPos.y(), width(), height());

        glDisable(GL_DEPTH_TEST);

//        glClearColor(0, 0, 0, 1);
//        glClear(GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

        //unbind everything
        m_program->disableAttributeArray(0);
        m_program->release();
}

void TextureRenderer::cleanup()
{
    if (m_program) {
        delete m_program;
        m_program = 0;
    }
}

void TextureRenderer::sync()
{
    m_thread_t = m_t;
}

} // namespace nmgui
