#include <SceneLoadMediatorCreator.h>
#include <FileSceneDirector.h>

std::shared_ptr<SceneLoadMediator> SceneLoadMediatorCreator::createMediator()
{
    if (_mediator == nullptr)
        createInstance();

    return _mediator;
}

void SceneLoadMediatorCreator::createInstance()
{
    static std::shared_ptr<SceneLoadMediator> mediator;

    if (!mediator)
    {
        std::shared_ptr<BaseSceneDirector> director;
        director = std::shared_ptr<BaseSceneDirector>(new FileSceneDirector);
        mediator = std::make_shared<SceneLoadMediator>(director);
    }

    _mediator = mediator;
}


