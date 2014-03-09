#ifndef NMGUI_HEIGHTMAPTERRAINRENDERER_HPP
#define NMGUI_HEIGHTMAPTERRAINRENDERER_HPP

#include "rendering/transform3d.hpp"

#include <string>

#include <QRectF>
#include <QtGui/qopenglshaderprogram.h>

namespace nmgui {

class HeightMapTerrainRenderer
{
public:
    explicit HeightMapTerrainRenderer();
    virtual ~HeightMapTerrainRenderer();
    void setGeneratorSource(std::string src){m_generatorFunctionSource = src; m_sourceDirty = true;}
    void setDomain(QRectF domain){m_domain = domain; }
    void render();

private:
    QOpenGLShaderProgram *m_program;
    QRectF m_domain;
    bool m_sourceDirty;
    std::string m_generatorFunctionSource;
    Transform3D m_camera;
    void recompileProgram();
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPTERRAINRENDERER_HPP
