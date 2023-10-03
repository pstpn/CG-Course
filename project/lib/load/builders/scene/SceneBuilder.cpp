#include "SceneBuilder.h"

SceneBuilder::SceneBuilder() 
{
    _loader = std::make_shared<FileCarcassModelLoader>();
}

void SceneBuilder::build()
{
    _scene = std::make_shared<Scene>();
}

size_t SceneBuilder::buildCount()
{
   return _loader->loadCount();
}

void SceneBuilder::buildObject(const std::shared_ptr<BaseObject> &object)
{
    _scene->addObject(object);
}


bool SceneBuilder::isBuild() const
{
    return _scene != nullptr;
}


std::shared_ptr<Scene> SceneBuilder::get()
{
    return _scene;
}

void SceneBuilder::open(std::string &fileName) {
    _loader->open(fileName);
}

void SceneBuilder::close() {
    _loader->close();
}
