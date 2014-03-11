#include "heightmapterrainmesh.hpp"

#include <QVector3D>
#include <QVector>

namespace nmgui {

HeightMapTerrainMesh::HeightMapTerrainMesh()
{
    QVector<QVector3D> vertices;
    vertices.append({1,0,0}); //bot right
    vertices.append({0,0,0}); //bot left
    vertices.append({0,0,1}); //top left
    vertices.append({1,0,1}); //top right
}

} // namespace nmgui
