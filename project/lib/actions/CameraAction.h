#pragma once

#include <memory>
#include <cstddef>

#include "BaseAction.h"

using ID = std::shared_ptr<std::size_t>;

class CameraAction : public BaseAction
{};

class AddCamera: public CameraAction {

    using Action = size_t(SceneManager::*)(const Vertex &location, const Vertex &direction);
    
public:
    AddCamera(const ID &id, const Vertex &location, const Vertex &direction);

    virtual void execute() override;

private:
    ID _id;
    Vertex _location;
    Vertex _direction;

    Action _method;
};


class RemoveCamera: public CameraAction
{
    using Action = void(SceneManager::*)(const size_t id);
public:
    RemoveCamera(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};


class TranslateCamera: public CameraAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &dx, const double &dy, const double &dz);
public:
    TranslateCamera(const std::shared_ptr<Camera> camera, const double dx, const double dy, const double dz);

    virtual void execute() override;

private:
    std::shared_ptr<Camera> _camera;
    double _dx, _dy, _dz;
    Action _method;
};


class RotateCamera: public CameraAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &ax, const double &ay, const double &az);
public:
    RotateCamera(const std::shared_ptr<Camera> camera, const double ax, const double ay, const double az);

    virtual void execute() override;

private:
    std::shared_ptr<Camera> _camera;
    double _ax, _ay, _az;
    Action _method;
};


class SetCamera: public CameraAction
{
    using Action = void(SceneManager::*)(size_t id);
public:
    explicit SetCamera(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};
