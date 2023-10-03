#pragma once

#include <memory>

#include "BaseManager.h"
#include "BaseModel.h"
#include "BaseLoadMediator.h"
#include "SceneLoadMediator.h"
#include "ModelLoadMediator.h"

class LoadManager : BaseManager
{
public:
    LoadManager() = default;
    LoadManager(const LoadManager &manager) = delete;
    LoadManager &operator = (const LoadManager &manager) = delete;

    ~LoadManager() = default;

    std::shared_ptr<BaseObject> load(std::string &name);
    std::shared_ptr<Scene> loadScene(std::string &name);
    void setMediator(std::shared_ptr<BaseLoadMediator> mediator);
    void setSceneMediator(std::shared_ptr<SceneLoadMediator> mediator);

private:
    std::shared_ptr<BaseLoadMediator> _mediator;
    std::shared_ptr<SceneLoadMediator> _sceneMediator;
};
