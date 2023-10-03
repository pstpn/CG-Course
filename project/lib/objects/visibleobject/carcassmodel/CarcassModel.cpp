#include <CarcassModel.h>

CarcassModel::CarcassModel(const std::shared_ptr<Side> &model_structure)
    : _side(model_structure)
{
}

CarcassModel::CarcassModel()
    : _side(new Side)
{
}

CarcassModel::CarcassModel(const CarcassModel &model)
{
    _side = model._side;
    _id = model._id;
}

Vertex CarcassModel::getOrigin() const
{
    return _side->getOrigin();
}