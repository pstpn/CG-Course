#pragma once

#include <memory>

#include "BaseAction.h"

#include "ManagerSolution.h"
#include "DrawManagerCreator.h"
#include "SceneManagerCreator.h"
#include "TransformManagerCreator.h"
#include "LoadManagerCreator.h"

#include "MediatorSolution.h"
#include "ModelLoadMediatorCreator.h"
#include "SceneLoadMediatorCreator.h"

class Facade
{
public:
    Facade();
    ~Facade() = default;

    void execute(BaseAction &command);
private:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transforManager;
    std::shared_ptr<ModelLoadMediator> _modelLoadMediator;
    std::shared_ptr<SceneLoadMediator> _sceneLoadMediator;
    std::shared_ptr<DrawCompositeAdapter> _drawCompositeAdapter;
};

