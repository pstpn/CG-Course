#include <Composite.h>
#include "Transformer.h"

Composite::Composite(std::shared_ptr<BaseObject> &element)
{
    _elements.emplace_back(element);
    updateOrigin();
}


Composite::Composite(const std::vector<std::shared_ptr<BaseObject>> &vector)
{
    _elements = vector;
    updateOrigin();
}


bool Composite::add(const std::shared_ptr<BaseObject> &element)
{
    _elements.emplace_back(element);
    updateOrigin();

    return true;
}


bool Composite::remove(const Iterator &iter)
{
    _elements.erase(iter);
    updateOrigin();

    return true;
}

void Composite::updateOrigin()
{
    _origin = Vertex(0);

    for (const auto &element : _elements)
    {
        _origin = _origin + element->getOrigin();
    }

    size_t count = _elements.size();
    _origin = Vertex(
        _origin.getX() / count,
        _origin.getY() / count,
        _origin.getZ() / count
    );
}

bool Composite::isVisible() const
{
    return false;
}

bool Composite::isComposite() const
{
    return true;
}

Vertex Composite::getOrigin() const
{
    return _origin;
}

Iterator Composite::begin()
{
    return _elements.begin();
}


Iterator Composite::end()
{
    return _elements.end();
}
