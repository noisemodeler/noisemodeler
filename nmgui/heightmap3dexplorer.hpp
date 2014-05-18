#ifndef NMGUI_HEIGHTMAP3DEXPLORER_HPP
#define NMGUI_HEIGHTMAP3DEXPLORER_HPP

#include "rendering/transform3d.hpp" //this inclusion looks kind of weird

#include <QtQuick/QQuickFramebufferObject>
#include <QtGui/QOpenGLShaderProgram>
#include <nmlib/model.hpp>

namespace nmgui {

class HeightMap3DFboRenderer;
class HeightMapFunction;

class HeightMap3DExplorer : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(float heightScale READ heightScale WRITE setHeightScale NOTIFY heightScaleChanged)
    Q_PROPERTY(float widthScale READ widthScale WRITE setWidthScale NOTIFY widthScaleChanged)
    Q_PROPERTY(nmgui::HeightMapFunction* heightMapFunction READ heightMapFunction WRITE setHeightMapFunction NOTIFY heightMapFunctionChanged)

public:
    struct State {
        QPointF center;
        float heightScale, widthScale;
        std::string shaderSource; //might be cleaner to copy the graph into state, then generate the shader source in the renderer
        Transform3D camera;
        State():
            center(0,0),
            heightScale(1),
            widthScale(1),
            shaderSource("void elevation(in vec2 coords, out float height){height = 0.5;}"),
            camera()
        {
            camera.setPosition({0,100,0});
            camera.yaw(-45);
            camera.pitch(-30);
//            camera.lookAt({0,0,0});
        }
    };

    explicit HeightMap3DExplorer(QQuickItem *the_parent = 0);

    HeightMapFunction *heightMapFunction() {return m_heightMapFunction;}
    void setHeightMapFunction(HeightMapFunction *heightMapFunction);

    //QQuickFrameBufferObject
    Renderer *createRenderer() const override;

    void setCenter(QPointF center);
    void setHeightScale(float scale);
    void setWidthScale(float scale);
    float heightScale(){ return m_state.heightScale; }
    float widthScale(){ return m_state.widthScale; }
    QPointF center(){ return m_state.center; }

    Q_INVOKABLE void yawCamera(float degrees);
    Q_INVOKABLE void pitchCamera(float degrees);
    Q_INVOKABLE void moveCameraForward(float distance);
    Q_INVOKABLE void moveCameraRight(float distance);

signals:
    void centerChanged();
    void heightScaleChanged();
    void widthScaleChanged();
    void heightMapFunctionChanged();

private slots:
    void updateShaderSource();

private:
    HeightMapFunction* m_heightMapFunction;
    State m_state;

    friend class HeightMap3DFboRenderer;
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAP3DEXPLORER_HPP
