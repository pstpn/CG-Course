#pragma once

#include "BaseLoadMediator.h"
#include "BaseModelDirector.h"
#include "BaseModelBuilder.h"

class ModelLoadMediator : public BaseLoadMediator
{
public:
    ModelLoadMediator() = default;
    explicit ModelLoadMediator(std::shared_ptr<BaseModelDirector> director);

    ~ModelLoadMediator() = default;

    std::shared_ptr<BaseObject> load(std::string &filename) override;

private:
    std::shared_ptr<BaseModelBuilder> _builder;
    std::shared_ptr<BaseModelDirector> _director;
};
