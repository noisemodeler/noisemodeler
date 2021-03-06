#include "heightmap3dexplorer.hpp"

#include "rendering/heightmap3drenderer.hpp"

#include "moduleq.hpp"
#include "heightmapfunction.hpp"
#include "inputlinkq.hpp"
#include "outputlinkq.hpp"

#include <nmlib/codegeneration/glsl/glslgenerator.hpp>

#include <QtQuick/qquickwindow.h>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <sstream>

namespace nmgui {

class HeightMap3DFboRenderer : public QQuickFramebufferObject::Renderer {

public:
    explicit HeightMap3DFboRenderer(bool visible):
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
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        m_heightMapRenderer.setAspectRatio(size.width(), size.height());
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::Depth);
        return new QOpenGLFramebufferObject(size, format);
    }

    //this is the only function where it is safe to communicate with the QQuickFrameBufferObject
    void synchronize(QQuickFramebufferObject *fbo) override
    {
        HeightMap3DExplorer* heightMapExplorer = dynamic_cast<HeightMap3DExplorer*>(fbo);
        m_heightMapRenderer.setState(heightMapExplorer->m_state);
        m_visible = fbo->isVisible();
    }
private:
    HeightMap3DRenderer m_heightMapRenderer;
    bool m_visible;
};



HeightMap3DExplorer::HeightMap3DExplorer(QQuickItem *the_parent) :
    QQuickFramebufferObject(the_parent),
    m_heightMapFunction(nullptr),
    m_state()
{
    connect(this, &HeightMap3DExplorer::heightMapFunctionChanged,
            this, &HeightMap3DExplorer::updateShaderSource);
    connect(this, &HeightMap3DExplorer::visibleChanged,
            this, &HeightMap3DExplorer::update);
}

void HeightMap3DExplorer::updateShaderSource()
{
    if(!m_heightMapFunction->valid())return;
    m_state.shaderSource = nm::glsl::GlslGenerator::compileToGlslFunction(
                *m_heightMapFunction->inputLink()->inputLink(),
                *m_heightMapFunction->outputLink()->outputLink(),
                "elevation");
    update();
}

QQuickFramebufferObject::Renderer *HeightMap3DExplorer::createRenderer() const
{
    return new HeightMap3DFboRenderer(isVisible());
}

void HeightMap3DExplorer::yawCamera(float degrees)
{
    m_state.camera.yaw(degrees);
    update();
}

void HeightMap3DExplorer::pitchCamera(float degrees)
{
    m_state.camera.pitch(degrees);
    update();
}

void HeightMap3DExplorer::moveCameraForward(float distance)
{
    m_state.camera.moveForward(distance);
    update();
}

void HeightMap3DExplorer::moveCameraRight(float distance)
{
    m_state.camera.moveRight(distance);
    update();
}

void HeightMap3DExplorer::setHeightMapFunction(HeightMapFunction *heightMapFunction)
{
    if(heightMapFunction==m_heightMapFunction)return;
    if(m_heightMapFunction!=nullptr)disconnect(m_heightMapFunction, 0, this, 0);
    m_heightMapFunction = heightMapFunction;
    connect(m_heightMapFunction, &HeightMapFunction::functionChanged, this, &HeightMap3DExplorer::updateShaderSource);
    emit heightMapFunctionChanged();
}

void HeightMap3DExplorer::setCenter(QPointF center){
    if(m_state.center==center)return;
    m_state.center = center;
    update();
    centerChanged();
}

void HeightMap3DExplorer::setTexturingEnabled(bool enabled)
{
    if(m_state.texturingEnabled==enabled)return;
    m_state.texturingEnabled = enabled;
    update();
    texturingEnabledChanged();
}

void HeightMap3DExplorer::setHeightScale(float scale)
{
    if(scale==m_state.heightScale)return;
    m_state.heightScale = scale;
    update();
    heightScaleChanged();
}

void HeightMap3DExplorer::setWidthScale(float scale)
{
    if(scale==m_state.widthScale)return;
    m_state.widthScale = scale;
    update();
    widthScaleChanged();
}

HeightMap3DExplorer::State::State():
    center(0,0),
    heightScale(1),
    widthScale(1),
    shaderSource("void elevation(in vec2 coords, out float height){height = 0.5;}"),
    camera(),
    texturingEnabled(true)
{
    camera.setPosition({0,100,0});
    camera.yaw(-45);
    camera.pitch(-25);
    //            camera.lookAt({0,0,0});
}

} // namespace nmgui
