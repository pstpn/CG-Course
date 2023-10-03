#include <QDebug>

#include "CameraAction.h"

AddCamera::AddCamera(const ID &id, const Vertex &location, const Vertex &direction)
    : _id(id),
      _location(location),
      _direction(direction)
{
    _method = &SceneManager::addCamera;
}

void AddCamera::execute()
{
    (*_id) = (*(_sceneManager).*_method)(_location, _direction);
}


RemoveCamera::RemoveCamera(const std::size_t id) : _id(id)
{
    _method = &SceneManager::retranslateObject;
}

void RemoveCamera::execute()
{
    (*(_sceneManager).*_method)(_id);
}


TranslateCamera::TranslateCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy, const double dz)
    : _camera(camera),
      _dx(dx),
      _dy(dy),
      _dz(dz)
{
    _method = &TransformManager::translateObject;
}

void TranslateCamera::execute()
{
    (*(_transforManager).*_method)(_camera, _dx, _dy, _dz);
}

RotateCamera::RotateCamera(const std::shared_ptr<Camera> camera, const double ax, const double ay, const double az)
    : _camera(camera),
      _ax(ax),
      _ay(ay),
      _az(az)
{
    _method = &TransformManager::rotateObject;
}

void RotateCamera::execute()
{
    _camera->rotate({_ax, _ay, _az});
    (*(_transforManager).*_method)(_camera, _ax, _ay, _az);
}


SetCamera::SetCamera(const std::size_t id) : _id(id)
{
    _method = &SceneManager::setCamera;
}

void SetCamera::execute()
{
    (*(_sceneManager).*_method)(_id);
}
