#pragma once

#include "Side.h"
#include "CarcassModel.h"
#include "BaseBuilder.h"

#include "FileCarcassModelLoader.h"

class BaseModelBuilder : public BaseBuilder
{
public:
    friend class FileCarcassModelLoader;

    BaseModelBuilder() = default;
    ~BaseModelBuilder() = default;

    virtual void open(std::string &fileName) = 0;
    virtual void close() = 0;

    virtual void build() override = 0;
    virtual bool isBuild() const override = 0;

    virtual std::vector<Vertex> buildVertices() = 0;
    virtual std::vector<Edge> buildEdges(int &amount) = 0;
    virtual void buildVertex(const Vertex &point) = 0;
    virtual void buildEdge(const Edge &edge) = 0;

    virtual std::shared_ptr<CarcassModel> get() = 0;

protected:
    std::shared_ptr<Side> _model;
    std::shared_ptr<FileCarcassModelLoader> _loader;
};
