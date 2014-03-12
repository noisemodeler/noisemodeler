#ifndef NMGUI_TRANSFORM3D_HPP
#define NMGUI_TRANSFORM3D_HPP

#include <QQuaternion>
#include <QVector3D>

namespace nmgui {

class Transform3D
{
public:
    explicit Transform3D();

    QMatrix4x4 worldToLocalMatrix() const;

    const QVector3D& position() const { return m_position; }
    void setPosition(const QVector3D &position) { m_position = position; }

    const QQuaternion& orientation() const { return m_orientation; }
    void setOrientation(const QQuaternion &orientation) { m_orientation = orientation; }

    //convenience menthods
    void moveForward(float distance) { m_position += m_orientation.rotatedVector(QVector3D(0,0,-1)) * distance; }
    void moveRight(float distance) { m_position += m_orientation.rotatedVector(QVector3D(1,0,0)) * distance; }
    void yaw(float degrees){m_orientation *= QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), degrees);}
    void pitch(float degrees){m_orientation = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), degrees) * m_orientation;}
    void lookAt(QVector3D position);

private:
    QQuaternion m_orientation;
    QVector3D m_position;
};

} // namespace nmgui

#endif // NMGUI_TRANSFORM3D_HPP
