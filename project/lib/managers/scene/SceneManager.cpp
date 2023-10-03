#include <utility>
#include "SceneManager.h"


SceneManager::SceneManager()
{
    _scene = std::make_shared<Scene>();
}


std::shared_ptr<Scene> SceneManager::getScene() const
{
    return _scene;
}


std::shared_ptr<Camera> SceneManager::getCamera() const
{
    return _camera;
}

std::shared_ptr<BaseObject> SceneManager::getObject(const size_t id)
{
    return _scene->getObject(id);
}

std::shared_ptr<BaseObject> SceneManager::getObjects()
{
    return _scene->getObjects();
}

size_t SceneManager::addCamera(const Vertex &location, const Vertex &direction)
{
    return _scene->addCamera(location, direction);
}

size_t SceneManager::addObject(const shared_ptr<BaseObject> &object)
{
    return _scene->addObject(object);
}

void SceneManager::retranslateObject(const size_t id)
{
    Iterator object_iter = _scene->getObjectIter(id);
    _scene->deleteObject(object_iter);
}


void SceneManager::setScene(std::shared_ptr<Scene> &scene)
{
    _scene = std::move(scene);
}


void SceneManager::setCamera(const std::size_t id)
{
    _camera = std::dynamic_pointer_cast<Camera>(*_scene->getObjectIter(id));
}
