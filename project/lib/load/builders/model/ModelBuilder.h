#pragma once 

#include "BaseModelBuilder.h"

class ModelBuilder : public BaseModelBuilder
{
public:
    ModelBuilder();
    ~ModelBuilder() = default;

    void build();

    std::vector<Vertex> buildVertices();
    std::vector<Edge> buildEdges(int &amount) ;

    void open(std::string &fileName);
    void close();

    void buildVertex(const Vertex &point);
    void buildEdge(const Edge &edge);
    bool isBuild() const ;

    std::shared_ptr<CarcassModel> get();
};

