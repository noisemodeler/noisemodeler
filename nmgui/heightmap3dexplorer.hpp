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
    Q_PROPERTY(bool texturingEnabled READ texturingEnabled WRITE setTexturingEnabled NOTIFY texturingEnabledChanged)

public:
    struct State {
        QPointF center;
        float heightScale, widthScale;
        std::string shaderSource; //might be cleaner to copy the graph into state, then generate the shader source in the renderer
        Transform3D camera;
        bool texturingEnabled;
        State();
    };

    explicit HeightMap3DExplorer(QQuickItem *the_parent = nullptr);

    HeightMapFunction *heightMapFunction() {return m_heightMapFunction;}
    void setHeightMapFunction(HeightMapFunction *heightMapFunction);

    //QQuickFrameBufferObject
    Renderer *createRenderer() const override;

    void setHeightScale(float scale);
    void setWidthScale(float scale);
    void setCenter(QPointF center);
    void setTexturingEnabled(bool enabled);
    float heightScale(){ return m_state.heightScale; }
    float widthScale(){ return m_state.widthScale; }
    QPointF center(){ return m_state.center; }
    bool texturingEnabled(){ return m_state.texturingEnabled; }

    Q_INVOKABLE void yawCamera(float degrees);
    Q_INVOKABLE void pitchCamera(float degrees);
    Q_INVOKABLE void moveCameraForward(float distance);
    Q_INVOKABLE void moveCameraRight(float distance);

signals:
    void centerChanged();
    void heightScaleChanged();
    void widthScaleChanged();
    void heightMapFunctionChanged();
    void texturingEnabledChanged();

private slots:
    void updateShaderSource();

private:
    HeightMapFunction* m_heightMapFunction;
    State m_state;

    friend class HeightMap3DFboRenderer;
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAP3DEXPLORER_HPP
