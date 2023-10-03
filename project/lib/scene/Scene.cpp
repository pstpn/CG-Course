#include <iterator>

#include "Scene.h"
#include "Composite.h"

#include <QDebug>

Scene::Scene()
    : _objects(new Composite)
{
}

std::size_t Scene::addObject(const std::shared_ptr<BaseObject> &object)
{
    // if (object->isVisible())
    //     _visible_objects->add(object);
    // else
    //     _invisible_objects->add(object);
    _objects->add(object);
    return object->getId();
}

std::size_t Scene::addCamera(const Vertex &location, const Vertex &direction)
{
    auto camera = std::make_shared<Camera>(location, direction);
    // _invisible_objects->add(camera);
    _objects->add(camera);

    return camera->getId();
}

void Scene::deleteObject(Iterator &iter)
{
    // if ((*iter)->isVisible())
    //     _visible_objects->remove(iter);
    // else
    //     _invisible_objects->remove(iter);
    _objects->remove(iter);
}

Iterator Scene::getObjectIter(const std::size_t id)
{
    auto iter = begin();
    
    for (; iter != end() && (*iter)->getId() != id; ++iter);

    // if (iter == end())
    // {
    //     iter = begin();
    //     for (; iter != end() && (*iter)->getId() != id; ++iter);
    // }

    return iter;
}

std::shared_ptr<BaseObject> Scene::getObject(const std::size_t id)
{
    return *getObjectIter(id);
}

// std::shared_ptr<BaseObject> Scene::getVisibleObjects()
// {
//     return _objects;
// }

std::shared_ptr<BaseObject> Scene::getObjects()
{
    return _objects;
}

// Iterator Scene::begin()
// {
//     return _objects->begin();
// }

// Iterator Scene::end()
// {
//     return _objects->end();
// }

Iterator Scene::begin()
{
    return _objects->begin();
}

Iterator Scene::end()
{
    return _objects->end();
}

// Iterator Scene::begin()
// {
//     return _objects->begin();
// }

// Iterator Scene::end()
// {
//     return _objects->end();
// }
