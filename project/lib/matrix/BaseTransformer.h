#pragma once

#include "Matrix.h"
#include "Vertex.h"

class BaseTransformer {

public:
    BaseTransformer() = default;
    virtual void transform(Vertex &vert) = 0;

    ~BaseTransformer() = default;
};