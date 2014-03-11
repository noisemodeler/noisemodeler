#ifndef NMGUI_HEIGHTMAPTEXTURERENDERER_HPP
#define NMGUI_HEIGHTMAPTEXTURERENDERER_HPP

#include "rendering/transform3d.hpp"
#include "heightmaptextureexplorer.hpp"

#include <string>

#include <QRectF>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

namespace nmgui {

class HeightMapTextureRenderer
{
public:
    explicit HeightMapTextureRenderer();
    virtual ~HeightMapTextureRenderer();
    void setState(HeightMapTextureExplorer::State& state);
    void render();

private:
    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_gridVerticesBuffer;
    HeightMapTextureExplorer::State m_state;
    bool m_sourceDirty;
    void initialize();
    void prepareVertexBuffer();
    void prepareVertexArrayObject();
    void recompileProgram();
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAPTEXTURERENDERER_HPP
