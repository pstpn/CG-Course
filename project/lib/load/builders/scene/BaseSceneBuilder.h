#pragma once 

#include "Scene.h"
#include "BaseBuilder.h"

class BaseSceneBuilder : public BaseBuilder
{
public:
    BaseSceneBuilder() = default;
    ~BaseSceneBuilder() = default;

    virtual void build() = 0;

    virtual size_t buildCount() = 0;
    virtual void buildObject(const std::shared_ptr<BaseObject> &object) = 0;
    virtual bool isBuild() const = 0;

    virtual void open(std::string &fileName) = 0;
    virtual void close() = 0;

    virtual std::shared_ptr<Scene> get() = 0;

protected:
    std::shared_ptr<Scene> _scene;
};

