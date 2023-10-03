#include <DrawCarcassModelAdapter.h>
#include <QColor>

#include <cmath>

#include "Transformer.h"

void DrawCarcassModelAdapter::setCamera(std::shared_ptr<Camera> camera)
{
    _camera = camera;
}

void DrawCarcassModelAdapter::setDrawer(std::shared_ptr<BaseDrawer> drawer)
{
    _drawer = drawer;
}

Vertex DrawCarcassModelAdapter::getProjection(const Vertex &point)
{
    Vertex projection = point;

    Transformer transfomer;
    transfomer.setRotationMatrix(
        _camera->_angle.getX(),
        _camera->_angle.getY(),
        _camera->_angle.getZ()
    );

    transfomer.transform(projection);
    return projection + _camera->_location;
}

void DrawCarcassModelAdapter::request()
{
    if (_adaptee && _camera && _drawer)
    {
        auto points = _adaptee->_side->getVertices();
        auto edges = _adaptee->_side->getEdges();
        auto center = _adaptee->_side->getOrigin();

        for (const auto &edge : edges)
        {
            _drawer->drawLine(
                getProjection(points.at(edge.getStart() - 1)).getAbsVertex(center),
                getProjection(points.at(edge.getEnd() - 1)).getAbsVertex(center)
            );
        }
    }
}
