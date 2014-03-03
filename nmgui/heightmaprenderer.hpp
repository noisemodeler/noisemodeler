#ifndef NMGUI_HEIGHTMAPRENDERER_HPP
#define NMGUI_HEIGHTMAPRENDERER_HPP

#include <string>

#include <QRectF>
#include <QtGui/qopenglshaderprogram.h>

namespace nmgui {

class HeightMapRenderer
{
public:
    explicit HeightMapRenderer();
    virtual ~HeightMapRenderer();
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

#endif // NMGUI_HEIGHTMAPRENDERER_HPP
