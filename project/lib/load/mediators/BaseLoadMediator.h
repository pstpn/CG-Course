#pragma once

#include <memory>

#include "BaseObject.h"

class BaseLoadMediator
{
public:
    BaseLoadMediator() = default;
    ~BaseLoadMediator() = default;

    virtual std::shared_ptr<BaseObject> load(std::string &filename) = 0;
};
