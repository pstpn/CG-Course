#pragma once

#include <ModelAdapter.h>
#include <Camera.h>
#include <Transformer.h>

class TransformCarcassModelAdapter : public ModelAdapter
{
public:
    virtual void setTransformer(const std::shared_ptr<BaseTransformer> &transformer);
    virtual void setOrigin(const Vertex &origin);

    virtual void request() override;

private:
    std::shared_ptr<BaseTransformer> _transformer;
    Vertex _origin;
};