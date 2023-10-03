#include "CameraLoadMediatorCreator.h"
#include "FileCameraDirector.h"

std::shared_ptr<CameraLoadMediator> CameraLoadMediatorCreator::createMediator()
{
    if (nullptr == _mediator)
        createInstance();

    return _mediator;
}

void CameraLoadMediatorCreator::createInstance()
{
    static std::shared_ptr<CameraLoadMediator> mediator;

    if (!mediator)
    {
        std::shared_ptr<BaseCameraDirector> director;
        director = std::shared_ptr<BaseCameraDirector>(new FileCameraDirector);
        mediator = std::make_shared<CameraLoadMediator>(director);
    }

    _mediator = mediator;
}


