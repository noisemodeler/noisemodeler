#include "camera.hpp"

namespace nmgui {

Camera::Camera(QObject *parent) :
    QObject(parent),
    orientation(1, 1, 0, 0)
{
}

} // namespace nmgui
