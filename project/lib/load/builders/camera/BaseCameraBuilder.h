#pragma once

#include "Camera.h"
#include "BaseBuilder.h"

class BaseCameraBuilder : public BaseBuilder
{
public:

    friend class FileCarcassModelLoader;

    BaseCameraBuilder() = default;
    ~BaseCameraBuilder() = default;

    virtual void open(std::string &fileName) = 0;
    virtual void close() = 0;

    virtual void build() = 0;
    virtual void buildLocation() = 0;
    virtual bool isBuild() const = 0;

    virtual std::shared_ptr<Camera> get() = 0;

protected:
    std::shared_ptr<Camera> _camera;
    // std::shared_ptr<FileCarcassModelLoader> _loader;
};
