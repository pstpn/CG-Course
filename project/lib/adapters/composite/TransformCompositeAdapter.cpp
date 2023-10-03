#include "TransformCompositeAdapter.h"
#include "TransformCarcassModelAdapter.h"

void TransformCompositeAdapter::setTransformer(const std::shared_ptr<BaseTransformer> &transformer)
{
    _transformer = transformer;
}

void TransformCompositeAdapter::setOrigin(const Vertex &origin)
{
    _origin = origin;
}

void TransformCompositeAdapter::request()
{
    moveElemsToOrigin(_origin);
    transformElems(_transformer);
    moveElemsToCenter(_origin);
}

void TransformCompositeAdapter::moveElemsToOrigin(const Vertex &center)
{
    Vertex diff = Vertex(0) - center;

    std::shared_ptr<Transformer> transformer = std::make_shared<Transformer>();
    transformer->setTranslationMatrix(diff.getX(), diff.getY(), diff.getZ());
    transformElems(transformer);
    _adaptee->updateOrigin();
}

void TransformCompositeAdapter::moveElemsToCenter(const Vertex &center)
{
    Vertex diff = center - _origin;

    std::shared_ptr<Transformer> transformer = std::make_shared<Transformer>();;
    transformer->setTranslationMatrix(diff.getX(), diff.getY(), diff.getZ());
    transformElems(transformer);

    _adaptee->updateOrigin();
}

void TransformCompositeAdapter::transformElems(const std::shared_ptr<BaseTransformer> &transformer)
{
    for (const auto &elem : _adaptee->_elements)
    {
        if (elem->isComposite())
        {
            auto adapter = TransformCompositeAdapter();
            adapter.setTransformer(_transformer);
            adapter.setAdaptee(std::dynamic_pointer_cast<Composite>(elem));
            adapter.setOrigin(elem->getOrigin());

            adapter.request();
        }
        else
        {
            auto adapter = TransformCarcassModelAdapter();
            adapter.setTransformer(_transformer);
            adapter.setAdaptee(std::dynamic_pointer_cast<CarcassModel>(elem));
            adapter.setOrigin(elem->getOrigin());

            adapter.request();
        }
    }
}