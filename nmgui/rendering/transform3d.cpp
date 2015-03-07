#include "transform3d.hpp"

#include <QMatrix4x4>
#include <cmath>

namespace nmgui {

Transform3D::Transform3D() :
    m_orientation(1, QVector3D(0,0,0)),
    m_position(0,0,0)
{
}

QMatrix4x4 Transform3D::worldToLocalMatrix() const
{
    QMatrix4x4 wtl;
    wtl.rotate(m_orientation.conjugate());
    wtl.translate(-m_position);
    return wtl;
}

void Transform3D::yaw(float degrees){
    QQuaternion yRotation = QQuaternion::fromAxisAndAngle(QVector3D(0,1,0), degrees);
    m_orientation = yRotation * m_orientation;
}



/* Build a unit quaternion representing the rotation
 * from u to v. The input vectors need not be normalised. */
QQuaternion fromTwoVectors(QVector3D u, QVector3D v)
{
    float norm_u_norm_v = sqrt(QVector3D::dotProduct(u, u) * QVector3D::dotProduct(v, v));
    float real_part = norm_u_norm_v + QVector3D::dotProduct(u, v);
    QVector3D w;
    if (real_part < 1.e-6f * norm_u_norm_v)
    {
        /* If u and v are exactly opposite, rotate 180 degrees
         * around an arbitrary orthogonal axis. Axis normalisation
         * can happen later, when we normalise the quaternion. */
        real_part = 0.0f;
        w = fabs(u.x()) > fabs(u.z()) ? QVector3D(-u.y(), u.x(), 0.f)
                                      : QVector3D(0.f,   -u.z(), u.y());
    } else {
        /* Otherwise, build quaternion the standard way. */
        w = QVector3D::crossProduct(u, v);
    }
    return QQuaternion(real_part, w).normalized();
}

void Transform3D::lookAt(QVector3D position)
{
    QVector3D direction = (position - m_position).normalized();
    //TODO, preserve up
    setOrientation(fromTwoVectors(QVector3D(0,0,-1), direction));
}

} // namespace nmgui
