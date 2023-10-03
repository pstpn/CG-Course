
#include "TransformCarcassModelAdapter.h"

void TransformCarcassModelAdapter::setTransformer(const std::shared_ptr<BaseTransformer> &transformer)
{
    _transformer = transformer;
}

void TransformCarcassModelAdapter::setOrigin(const Vertex &origin)
{
    _origin = origin;
}

void TransformCarcassModelAdapter::request()
{
    if (_adaptee && _transformer)
    {
        _adaptee->_side->transform(_transformer, _origin);
    }
}
