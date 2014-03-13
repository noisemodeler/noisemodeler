#ifndef NMGUI_HEIGHTMAP3DRENDERER_HPP
#define NMGUI_HEIGHTMAP3DRENDERER_HPP

#include "rendering/transform3d.hpp"
#include "heightmap3dexplorer.hpp"

#include <string>

#include <QRectF>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

namespace nmgui {

class HeightMap3DRenderer
{
public:
    explicit HeightMap3DRenderer();
    virtual ~HeightMap3DRenderer();
    void setState(HeightMap3DExplorer::State& state);
    void render();

private:
    static constexpr int c_resolution = 64; //width and height of a terrain patch
    QOpenGLShaderProgram *m_program;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_gridVerticesBuffer;
    HeightMap3DExplorer::State m_state;
    bool m_sourceDirty;
    int m_vertexCount;
    void initialize();
    void prepareVertexBuffer();
    void prepareVertexArrayObject();
    void recompileProgram();
};

} // namespace nmgui

#endif // NMGUI_HEIGHTMAP3DRENDERER_HPP
