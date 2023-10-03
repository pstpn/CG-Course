#pragma once

#include "BaseSceneDirector.h"
#include "SceneBuilder.h"

class SceneLoadMediator
{
public:
    SceneLoadMediator() = default;
    explicit SceneLoadMediator(std::shared_ptr<BaseSceneDirector> director);

    ~SceneLoadMediator() = default;

    std::shared_ptr<Scene> load(std::string &filename);
    virtual void setDirector(std::shared_ptr<BaseSceneDirector> director);

private:
    std::shared_ptr<SceneBuilder> _builder;
    std::shared_ptr<BaseSceneDirector> _director;
};
