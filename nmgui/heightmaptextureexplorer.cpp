#include "heightmaptextureexplorer.hpp"

#include "rendering/heightmaptexturerenderer.hpp"

#include "moduleq.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <nmlib/codegeneration/glsl/glslgenerator.hpp>

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>
#include <sstream>

namespace nmgui {

class HeightMapTextureFboRenderer : public QQuickFramebufferObject::Renderer {

public:
    HeightMapTextureFboRenderer(bool visible):
        QQuickFramebufferObject::Renderer(),
        m_visible(visible)
    {}
    // Renderer interface
protected:
    void render() override {
        if(m_visible){
            m_heightMapRenderer.render();
            update();
        }
    }
    //QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

    //this is the only function where it is safe to communicate with the QQuickFrameBufferObject
    void synchronize(QQuickFramebufferObject *fbo) override
    {
        HeightMapTextureExplorer* heightMapExplorer = dynamic_cast<HeightMapTextureExplorer*>(fbo);
        m_heightMapRenderer.setState(heightMapExplorer->m_state);
        m_visible = fbo->isVisible();
    }
private:
    HeightMapTextureRenderer m_heightMapRenderer;
    bool m_visible;
};



HeightMapTextureExplorer::HeightMapTextureExplorer(QQuickItem *the_parent) :
    QQuickFramebufferObject(the_parent),
    m_heightMapFunction(nullptr),
    m_state()
{
    connect(this, &HeightMapTextureExplorer::heightMapFunctionChanged,
            this, &HeightMapTextureExplorer::updateShaderSource);
    connect(this, &HeightMapTextureExplorer::visibleChanged,
            this, &HeightMapTextureExplorer::update);
}

void HeightMapTextureExplorer::updateShaderSource()
{
    if(!m_heightMapFunction->valid())return;
    m_state.shaderSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                *m_heightMapFunction->inputLink()->inputLink(),
                *m_heightMapFunction->outputLink()->outputLink(),
                "elevation");
    update();
}

QQuickFramebufferObject::Renderer *HeightMapTextureExplorer::createRenderer() const
{
    return new HeightMapTextureFboRenderer(isVisible());
}

void HeightMapTextureExplorer::setHeightMapFunction(HeightMapFunction *heightMapFunction)
{
    if(heightMapFunction==m_heightMapFunction)return;
    if(m_heightMapFunction!=nullptr)disconnect(m_heightMapFunction, 0, this, 0);
    m_heightMapFunction = heightMapFunction;
    connect(m_heightMapFunction, SIGNAL(functionChanged()), this, SLOT(updateShaderSource()));
    emit heightMapFunctionChanged();
}

void HeightMapTextureExplorer::setCenter(QPointF center){
    m_state.center = center;
    update();
    centerChanged();
}

void HeightMapTextureExplorer::setSize(QPointF size)
{
    m_state.size = size;
    update();
    sizeChanged();
}

} // namespace nmgui
