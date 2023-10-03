#pragma once

#include "BaseLoadMediator.h"
#include "BaseCameraDirector.h"

class CameraLoadMediator : public BaseLoadMediator
{
public:
    explicit CameraLoadMediator(std::shared_ptr<BaseCameraDirector> director);
    ~CameraLoadMediator() = default;

    std::shared_ptr<BaseObject> load(std::string &filename) override;

private:
    std::shared_ptr<BaseCameraBuilder> _builder;
    std::shared_ptr<BaseCameraDirector> _director;
};

