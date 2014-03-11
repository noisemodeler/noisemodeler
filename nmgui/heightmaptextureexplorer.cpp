#include "heightmaptextureexplorer.hpp"

#include "rendering/heightmaptexturerenderer.hpp"

#include "moduleq.hpp"

#include <nmlib/codegeneration/glsl/glslgenerator.hpp>

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>
#include <sstream>

namespace nmgui {

class HeightMapTextureFboRenderer : public QQuickFramebufferObject::Renderer {

    // Renderer interface
protected:
    void render() override {
        m_heightMapRenderer.render();
        update();
    }
    //QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    //this is the only function where it is safe to communicate with the QQuickFrameBufferObject
    void synchronize(QQuickFramebufferObject *fbo) override
    {
        HeightMapTextureExplorer* heightMapExplorer = dynamic_cast<HeightMapTextureExplorer*>(fbo);
        m_heightMapRenderer.setState(heightMapExplorer->m_state);
    }
private:
    HeightMapTextureRenderer m_heightMapRenderer;
};



HeightMapTextureExplorer::HeightMapTextureExplorer(QQuickItem *the_parent) :
    QQuickFramebufferObject(the_parent),
    m_state()
{
    connect(this, SIGNAL(heightMapFunctionChanged()), this, SLOT(updateShaderSource()));
}

void HeightMapTextureExplorer::updateShaderSource()
{
    if(m_heightMapFunction->inputLink() == nullptr || m_heightMapFunction->outputLink() == nullptr)return;
    m_state.shaderSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                m_heightMapFunction->inputLink()->inputLink(),
                m_heightMapFunction->outputLink()->outputLink(),
                "elevation");
    update();
}

QQuickFramebufferObject::Renderer *HeightMapTextureExplorer::createRenderer() const
{
    return new HeightMapTextureFboRenderer();
}

void HeightMapTextureExplorer::setHeightMapFunction(HeightMapFunction *heightMapFunction)
{
    if(heightMapFunction==m_heightMapFunction)return;
    if(m_heightMapFunction!=nullptr)disconnect(m_heightMapFunction, 0, this, 0);
    m_heightMapFunction = heightMapFunction;
    connect(m_heightMapFunction, SIGNAL(functionChanged()), this, SLOT(updateShaderSource()));
    emit heightMapFunctionChanged();
}

} // namespace nmgui
