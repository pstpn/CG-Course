#include "Facade.h"

Facade::Facade()
{
    _drawManager = ManagerSolution<DrawManagerCreator>().create();
    _loadManager = ManagerSolution<LoadManagerCreator>().create();
    _sceneManager = ManagerSolution<SceneManagerCreator>().create();
    _transforManager = ManagerSolution<TransformManagerCreator>().create();
    _modelLoadMediator = MediatorSolution<ModelLoadMediatorCreator>().create();
    _sceneLoadMediator = MediatorSolution<SceneLoadMediatorCreator>().create();;
    _drawCompositeAdapter = std::make_shared<DrawCompositeAdapter>();

    _loadManager->setMediator(_modelLoadMediator);
    _loadManager->setSceneMediator(_sceneLoadMediator);
    _drawManager->setAdapter(_drawCompositeAdapter);
}

void Facade::execute(BaseAction &command)
{
    command.setManagers(
        _drawManager,
        _loadManager,
        _sceneManager,
        _transforManager,
        _modelLoadMediator,
        _sceneLoadMediator,
        _drawCompositeAdapter
    );

    _drawManager->setCamera(_sceneManager->getCamera());
    command.execute();
}
