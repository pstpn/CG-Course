#include "Camera.h"

Camera::Camera(const Vertex &location, const Vertex &angles)
    : _location(location),
      _angle(angles)
{}

Vertex Camera::getOrigin() const
{
    return _location;
}

void Camera::rotate(const Vertex &angles)
{
    _angle += angles;
}
