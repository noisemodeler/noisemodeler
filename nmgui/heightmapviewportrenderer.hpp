#ifndef NMGUI_HEIGHTMAPVIEWPORTRENDERER_HPP
#define NMGUI_HEIGHTMAPVIEWPORTRENDERER_HPP

#include <string>

#include <QRectF>
#include <QOpenGLShaderProgram>

namespace nmgui {

class HeightMapViewportRenderer
{
public:
    explicit HeightMapViewportRenderer();
    virtual ~HeightMapViewportRenderer();
    void setGeneratorSource(std::string src){m_generatorFunctionSource = src; m_sourceDirty = true;}
    void setDomain(QRectF domain){m_domain = domain; }
    void render();

private:
    QOpenGLShaderProgram *m_program;
    QRectF m_domain;
    bool m_sourceDirty;
    std::string m_generatorFunctionSource;
    void recompileProgram();
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPVIEWPORTRENDERER_HPP
