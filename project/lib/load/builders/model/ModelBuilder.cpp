#include "ModelBuilder.h"

ModelBuilder::ModelBuilder()
{
    _loader = std::make_shared<FileCarcassModelLoader>();
}

void ModelBuilder::build()
{
    _model = std::make_shared<Side>();
}

void ModelBuilder::open(std::string &fileName)
{
    _loader->open(fileName);
}

void ModelBuilder::close()
{
    _loader->close();
}

std::vector<Vertex> ModelBuilder::buildVertices() {

    vector<Vertex> points = _loader->loadVertices();
    int ptsAmount = points.size();

    for (int i = 0; i < ptsAmount; ++i)
        buildVertex(points[i]);

    return points;
}

std::vector<Edge> ModelBuilder::buildEdges(int &amount) {

    std::vector<Edge> edges = _loader->loadEdges(amount);

    int edgesAmount = edges.size();

    for (int i = 0; i < edgesAmount; ++i)
        buildEdge(edges[i]);

    return edges;
}

void ModelBuilder::buildVertex(const Vertex &point)
{
    if (!isBuild()) { }

    _model->addVertex(point);
}


void ModelBuilder::buildEdge(const Edge &edge)
{
    if (!isBuild()) { }

    _model->addEdge(edge);
}


bool ModelBuilder::isBuild() const
{
    return _model != nullptr;
}

std::shared_ptr<CarcassModel> ModelBuilder::get()
{
    return std::make_shared<CarcassModel>(_model);
}
