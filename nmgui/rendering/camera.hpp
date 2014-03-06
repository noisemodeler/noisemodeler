#ifndef NMGUI_CAMERA_HPP
#define NMGUI_CAMERA_HPP

#include <QObject>
#include <QQuaternion>

namespace nmgui {

class Camera : public QObject
{
    Q_OBJECT
public:
    explicit Camera(QObject *parent = 0);

signals:

public slots:

private:
    QQuaternion orientation;
};

} // namespace nmgui

#endif // NMGUI_CAMERA_HPP
