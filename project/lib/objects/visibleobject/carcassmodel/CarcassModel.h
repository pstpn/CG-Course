#pragma once 

#include <memory>
#include <utility>

#include "BaseObject.h"
#include "BaseModel.h"
#include "Vertex.h"
#include "Edge.h"
#include "Side.h"

class CarcassModel : public BaseModel
{
    friend class DrawCarcassModelAdapter;
    friend class TransformCarcassModelAdapter;

public:
    CarcassModel();
    explicit CarcassModel(const std::shared_ptr<Side> &model_structure);
    CarcassModel(const CarcassModel &model);

    ~CarcassModel() override = default;

    virtual Vertex getOrigin() const override;

protected:
    std::shared_ptr<Side> _side;
};

