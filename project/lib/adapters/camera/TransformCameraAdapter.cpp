#include "TransformCameraAdapter.h"

void TransformCameraAdapter::setTransformer(const std::shared_ptr<BaseTransformer> &transformer)
{
    _transformer = transformer;
}

void TransformCameraAdapter::setOrigin(const Vertex &origin)
{
    _origin = origin;
}

void TransformCameraAdapter::request()
{
    if (_adaptee && _transformer)
    {
        Vertex diff = Vertex(0) - _origin;
        _adaptee->_location += diff;

        _transformer->transform(_adaptee->_location);

        _adaptee->_location -= diff;
    }
}
