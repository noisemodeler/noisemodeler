#include "heightmap3dexplorer.hpp"

#include "rendering/heightmap3drenderer.hpp"

#include "moduleq.hpp"

#include <nmlib/codegeneration/glsl/glslgenerator.hpp>

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>
#include <sstream>

namespace nmgui {

class HeightMap3DFboRenderer : public QQuickFramebufferObject::Renderer {

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
        HeightMap3DExplorer* heightMapExplorer = dynamic_cast<HeightMap3DExplorer*>(fbo);
        m_heightMapRenderer.setState(heightMapExplorer->m_state);
    }
private:
    HeightMap3DRenderer m_heightMapRenderer;
};



HeightMap3DExplorer::HeightMap3DExplorer(QQuickItem *the_parent) :
    QQuickFramebufferObject(the_parent),
    m_state()
{
    connect(this, SIGNAL(heightMapFunctionChanged()), this, SLOT(updateShaderSource()));
}

void HeightMap3DExplorer::updateShaderSource()
{
    m_state.shaderSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                m_heightMapFunction->inputLink()->inputLink(),
                m_heightMapFunction->outputLink()->outputLink(),
                "elevation");
    update();
}

QQuickFramebufferObject::Renderer *HeightMap3DExplorer::createRenderer() const
{
    return new HeightMap3DFboRenderer();
}

void HeightMap3DExplorer::setHeightMapFunction(HeightMapFunction *heightMapFunction)
{
    if(heightMapFunction==m_heightMapFunction)return;
    if(m_heightMapFunction!=nullptr)disconnect(m_heightMapFunction, 0, this, 0);
    m_heightMapFunction = heightMapFunction;
    connect(m_heightMapFunction, SIGNAL(functionChanged()), this, SLOT(updateShaderSource()));
    emit heightMapFunctionChanged();
}

} // namespace nmgui
