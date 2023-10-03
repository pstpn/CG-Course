#include "BaseAction.h"

void BaseAction::setManagers(std::shared_ptr<DrawManager> drawManager,
                             std::shared_ptr<LoadManager> loadManager,
                             std::shared_ptr<SceneManager> sceneManager,
                             std::shared_ptr<TransformManager> transforManager,
                             std::shared_ptr<ModelLoadMediator> modelLoadMediator,
                             std::shared_ptr<SceneLoadMediator> sceneLoadMediator,
                             std::shared_ptr<DrawCompositeAdapter> drawCompositeAdapter)
{
    _drawManager = drawManager;
    _loadManager = loadManager;
    _sceneManager = sceneManager;
    _transforManager = transforManager;
    _modelLoadMediator = modelLoadMediator;
    _sceneLoadMediator = sceneLoadMediator;
    _drawCompositeAdapter = drawCompositeAdapter;
}
