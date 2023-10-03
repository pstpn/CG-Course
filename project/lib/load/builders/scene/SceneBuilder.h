#pragma once

#include "BaseSceneBuilder.h"

class SceneBuilder : public BaseSceneBuilder
{
public:
    SceneBuilder();
    ~SceneBuilder() = default;

    void build() override;
    size_t buildCount();
    void buildObject(const std::shared_ptr<BaseObject> &object) override;
    bool isBuild() const override;

    std::shared_ptr<Scene> get() override;

    void open(std::string &fileName);
    void close();

private:
    std::shared_ptr<Scene> _scene;
};
