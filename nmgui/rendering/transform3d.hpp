#ifndef NMGUI_TRANSFORM3D_HPP
#define NMGUI_TRANSFORM3D_HPP

#include <QObject>
#include <QQuaternion>
#include <QVector3D>

namespace nmgui {

class Transform3D : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
public:
    explicit Transform3D(QObject *parent = 0);

    QVector3D position() const;
    void setPosition(const QVector3D &position);

    QQuaternion orientation() const;
    void setOrientation(const QQuaternion &orientation);

    void moveForward(float distance);
    void moveRight(float distance);
    void yaw(float angle);

    void lookAt(QVector3D position);

Q_SIGNALS:
    void positionChanged();
    void orientationChanged();

private:
    QQuaternion m_orientation;
    QVector3D m_position;
};

} // namespace nmgui

#endif // NMGUI_TRANSFORM3D_HPP
