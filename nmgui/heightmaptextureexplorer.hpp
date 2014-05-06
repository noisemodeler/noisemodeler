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


    //TODO domainless
    Q_PROPERTY(QRectF domain READ domain WRITE setDomain NOTIFY domainChanged)
    Q_PROPERTY(nmgui::HeightMapFunction* heightMapFunction READ heightMapFunction WRITE setHeightMapFunction NOTIFY heightMapFunctionChanged)

public:
    struct State {
        QRectF domain;
        std::string shaderSource; //might be cleaner to copy the graph into state, then generate the shader source in the renderer
        State():
            domain(0,0,1,1),
            shaderSource("void elevation(in vec2 coords, out float height){height = 0.5;}")
        {}
    };

    explicit HeightMapTextureExplorer(QQuickItem *the_parent = 0);

    HeightMapFunction *heightMapFunction() {return m_heightMapFunction;}
    void setHeightMapFunction(HeightMapFunction *heightMapFunction);

    QRectF domain() const {return m_state.domain;}
    void setDomain(QRectF domain){m_state.domain = domain; update(); domainChanged();}

    //QQuickFrameBufferObject
    Renderer *createRenderer() const override;

signals:
    void domainChanged();
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
