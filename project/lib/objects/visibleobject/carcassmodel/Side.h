#pragma once

#include <vector>

#include "Vertex.h"
#include "Edge.h"
#include "BaseTransformer.h"

class Side
{
public:
    Side() = default;
    Side(std::vector<Vertex> &vertices, std::vector<Edge> &edges);
    Side(std::vector<Vertex> &vertices, std::vector<Edge> &edges, Vertex &center);

    ~Side() = default;

    const std::vector<Vertex> &getVertices() const;
    const std::vector<Edge> &getEdges() const;
    const Vertex getOrigin() const;

    void addVertex(const Vertex &point);
    void addEdge(const Edge &edge);

    void moveVerticesToOrigin(const Vertex &center);
    void moveVerticesToCenter(const Vertex &center);
    void transformVertices(const shared_ptr<BaseTransformer> &transformer);
    void transform(const shared_ptr<BaseTransformer> &transformer, const Vertex &center);

private:
    void updateOrigin();
    Vertex _origin;

    std::vector<Vertex> _vertices;
    std::vector<Edge> _edges;
};
