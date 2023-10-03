#pragma once

#include "ModelLoadMediator.h"

class ModelLoadMediatorCreator
{
public:
    std::shared_ptr<ModelLoadMediator> createMediator();

private:
    void createInstance();

    std::shared_ptr<ModelLoadMediator> _mediator;
};
