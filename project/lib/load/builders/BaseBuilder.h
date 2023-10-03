#pragma once 

#include "FileCarcassModelLoader.h"

class BaseBuilder
{
    friend class FileCarcassModelLoader;
public:
    BaseBuilder() = default;
    ~BaseBuilder() = default;

    virtual void build() = 0;
    virtual bool isBuild() const = 0;

    virtual void open(std::string &fileName) = 0;
    virtual void close() = 0;

protected:
    std::shared_ptr<FileCarcassModelLoader> _loader;
};
