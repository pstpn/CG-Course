#include "LoadModelDirector.h"
#include "Exceptions.h"


std::shared_ptr<CarcassModel> LoadModelDirector::load(std::shared_ptr<BaseModelBuilder> builder, std::string &filename)
{
    builder->open(filename);

    builder->build();
    std::vector<Vertex> points = builder->buildVertices();
    int amount = points.size();
    std::vector<Edge> edges = builder->buildEdges(amount);

    builder->close();

    return builder->get();
}
