#ifndef NMGUI_HEIGHTMAPTEXTUREEXPLORER_HPP
#define NMGUI_HEIGHTMAPTEXTUREEXPLORER_HPP

#include "heightmapfunction.hpp"

#include <QtQuick/QQuickFramebufferObject>
#include <QtGui/QOpenGLShaderProgram>
#include <nmlib/model.hpp>

namespace nmgui {

class HeightMapTextureFboRenderer;
class HeightMapFunction;

class HeightMapTextureExplorer : public QQuickFramebufferObject
{
    Q_OBJECT

    Q_PROPERTY(QPointF center READ center WRITE setCenter NOTIFY centerChanged)
    Q_PROPERTY(QPointF size READ size WRITE setSize NOTIFY sizeChanged)
    Q_PROPERTY(nmgui::HeightMapFunction* heightMapFunction READ heightMapFunction WRITE setHeightMapFunction NOTIFY heightMapFunctionChanged)

public:
    struct State {
        QPointF center;
        QPointF size;
        std::string shaderSource; //might be cleaner to copy the graph into state, then generate the shader source in the renderer
        State():
            center(0,0),
            size(1,1),
            shaderSource("void elevation(in vec2 coords, out float height){height = 0.5;}")
        {}
    };

    explicit HeightMapTextureExplorer(QQuickItem *the_parent = nullptr);

    HeightMapFunction *heightMapFunction() {return m_heightMapFunction;}
    void setHeightMapFunction(HeightMapFunction *heightMapFunction);

    void setCenter(QPointF center);
    void setSize(QPointF size);
    QPointF size(){ return m_state.size; }
    QPointF center(){ return m_state.center; }

    //QQuickFrameBufferObject
    Renderer *createRenderer() const override;

signals:
    void centerChanged();
    void sizeChanged();
    void heightMapFunctionChanged();

private slots:
    void updateShaderSource();

private:
    HeightMapFunction* m_heightMapFunction;
    State m_state;

    friend class HeightMapTextureFboRenderer;
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPTEXTUREEXPLORER_HPP
