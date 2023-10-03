#include "LoadManager.h"

#include <QDebug>

std::shared_ptr<BaseObject> LoadManager::load(std::string &name)
{
    return _mediator->load(name);
}

std::shared_ptr<Scene> LoadManager::loadScene(std::string &name)
{
    return _sceneMediator->load(name);
}

void LoadManager::setMediator(std::shared_ptr<BaseLoadMediator> mediator)
{
    _mediator = mediator;
}

void LoadManager::setSceneMediator(std::shared_ptr<SceneLoadMediator> mediator)
{
    _sceneMediator = mediator;
}
