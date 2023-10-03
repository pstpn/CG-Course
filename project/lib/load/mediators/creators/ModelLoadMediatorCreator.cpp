#include <ModelLoadMediatorCreator.h>
#include <LoadModelDirector.h>

std::shared_ptr<ModelLoadMediator> ModelLoadMediatorCreator::createMediator()
{
    if (nullptr == _mediator)
        createInstance();

    return _mediator;
}

void ModelLoadMediatorCreator::createInstance()
{
    static std::shared_ptr<ModelLoadMediator> mediator;

    if (!mediator)
    {
        // auto reader = std::shared_ptr<FileCarcassModelLoader>(new FileCarcassModelLoader());
        // auto director = std::shared_ptr<BaseModelDirector>(new LoadModelDirector(reader));
        auto director = std::shared_ptr<BaseModelDirector>(new LoadModelDirector());
        mediator = std::make_shared<ModelLoadMediator>(director);
    }

    _mediator = mediator;
}
