#ifndef NMGUI_HEIGHTMAPTERRAINRENDERER_HPP
#define NMGUI_HEIGHTMAPTERRAINRENDERER_HPP

#include "rendering/transform3d.hpp"

#include <string>

#include <QRectF>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

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
    static constexpr int c_resolution = 2; //width and height of a terrain patch
    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_gridVerticesBuffer;
    QRectF m_domain;
    bool m_sourceDirty;
    std::string m_generatorFunctionSource;
    Transform3D m_camera;
    void initialize();
    void prepareVertexBuffer();
    void prepareVertexArrayObject();
    void recompileProgram();
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPTERRAINRENDERER_HPP
