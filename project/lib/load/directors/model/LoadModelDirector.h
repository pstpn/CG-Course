#pragma once

#include "BaseModelDirector.h"

class LoadModelDirector : public BaseModelDirector
{
public:
    LoadModelDirector() = default;

    ~LoadModelDirector() override = default;

    std::shared_ptr<CarcassModel> load(std::shared_ptr<BaseModelBuilder> builder, std::string &filename) override;
};
