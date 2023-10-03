
#pragma once

#include "DrawManager.h"
#include "LoadManager.h"
#include "SceneManager.h"
#include "TransformManager.h"
#include "CameraLoadMediator.h"
#include "ModelLoadMediator.h"
#include "SceneLoadMediator.h"
#include "DrawCompositeAdapter.h"

class BaseAction
{
public:
    BaseAction() = default;
    virtual ~BaseAction() = default;

    virtual void setManagers(std::shared_ptr<DrawManager> drawManager,
                             std::shared_ptr<LoadManager> loadManager,
                             std::shared_ptr<SceneManager> sceneManager,
                             std::shared_ptr<TransformManager> transforManager,
                             std::shared_ptr<ModelLoadMediator> modelLoadMediator,
                             std::shared_ptr<SceneLoadMediator> sceneLoadMediator,
                             std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter);

    virtual void execute() = 0;

protected:
    std::shared_ptr<DrawManager> _drawManager;
    std::shared_ptr<LoadManager> _loadManager;
    std::shared_ptr<SceneManager> _sceneManager;
    std::shared_ptr<TransformManager> _transforManager;
    std::shared_ptr<ModelLoadMediator> _modelLoadMediator;
    std::shared_ptr<SceneLoadMediator> _sceneLoadMediator;
    std::shared_ptr<DrawCompositeAdapter> _drawCompositeAdapter;
};
