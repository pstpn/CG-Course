#include "Side.h"
#include "Transformer.h"

Side::Side(std::vector<Vertex> &vertices, std::vector<Edge> &edges)
    : _origin { },
      _vertices(vertices),
      _edges(edges)
{
}


Side::Side(std::vector<Vertex> &vertices, std::vector<Edge> &edges, Vertex &center)
    : _origin(center),
      _vertices(vertices),
      _edges(edges)
{
}

const std::vector<Vertex> &Side::getVertices() const
{
    return _vertices;
}

const std::vector<Edge> &Side::getEdges() const
{
    return _edges;
}

const Vertex Side::getOrigin() const
{
    return _origin;
}

void Side::addVertex(const Vertex &point)
{
    _vertices.emplace_back(point);
    updateOrigin();
}

void Side::addEdge(const Edge &edge)
{
    _edges.emplace_back(edge);
}

void Side::updateOrigin()
{
    _origin = Vertex(0);

    for (const auto &element : _vertices)
        _origin = _origin + element.getOrigin();

    size_t count = _vertices.size();
    _origin = Vertex(
        _origin.getX() / count,
        _origin.getY() / count,
        _origin.getZ() / count
    );
}

void Side::moveVerticesToOrigin(const Vertex &center)
{
    Vertex diff = Vertex(0) - center;

    std::shared_ptr<Transformer> transformer = std::make_shared<Transformer>();
    transformer->setTranslationMatrix(diff.getX(),  diff.getY(),  diff.getZ());

    transformVertices(transformer);
    updateOrigin();
}

void Side::moveVerticesToCenter(const Vertex &center)
{
    Vertex diff = center - Vertex(0);

    std::shared_ptr<Transformer> transformer = std::make_shared<Transformer>();
    transformer->setTranslationMatrix(diff.getX(),  diff.getY(),  diff.getZ());

    transformVertices(transformer);
    updateOrigin();
}

void Side::transformVertices(const shared_ptr<BaseTransformer> &transformer)
{
    for (auto &vertex : _vertices)
        transformer->transform(vertex);
}

void Side::transform(const shared_ptr<BaseTransformer> &transformer, const Vertex &center)
{
    moveVerticesToOrigin(center);
    transformVertices(transformer);
    moveVerticesToCenter(center);
    updateOrigin();
}
