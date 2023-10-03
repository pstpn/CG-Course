#pragma once

#include "SceneLoadMediator.h"

class SceneLoadMediatorCreator
{
public:
    std::shared_ptr<SceneLoadMediator> createMediator();

private:
    void createInstance();

    std::shared_ptr<SceneLoadMediator> _mediator;
};


