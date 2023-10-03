#pragma once

#include "BaseCameraBuilder.h"

class CameraBuilder : public BaseCameraBuilder
{
public:
    CameraBuilder();
    ~CameraBuilder() = default;

    void build();
    void buildLocation();
    bool isBuild() const;

    virtual void open(std::string &fileName);
    virtual void close();

    std::shared_ptr<Camera> get();
};

