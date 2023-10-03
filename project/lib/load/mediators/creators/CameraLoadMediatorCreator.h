#pragma once

#include "CameraLoadMediator.h"
#include "BaseCameraDirector.h"

class CameraLoadMediatorCreator
{
public:
    std::shared_ptr<CameraLoadMediator> createMediator();

private:
    void createInstance();

    std::shared_ptr<CameraLoadMediator> _mediator;
};

