#include "ModelsAction.h"

TranslateModels::TranslateModels(const std::shared_ptr<BaseObject> objects, const double dx, const double dy, const double dz)
    : _objects(objects),
      _dx(dx),
      _dy(dy),
      _dz(dz)
{
    _method = &TransformManager::translateObject;
}

void TranslateModels::execute()
{
    (*(_transforManager).*_method)(_objects, _dx, _dy, _dz);
}


ScaleModels::ScaleModels(const std::shared_ptr<BaseObject> objects, const double kx, const double ky, const double kz)
    : _objects(objects),
      _kx(kx),
      _ky(ky),
      _kz(kz)
{
    _method = &TransformManager::scaleObject;
}

void ScaleModels::execute()
{
    (*(_transforManager).*_method)(_objects, _kx, _ky, _kz);
}


RotateModels::RotateModels(const std::shared_ptr<BaseObject> objects, const double ax, const double ay, const double az)
    : _objects(objects),
      _ax(ax),
      _ay(ay),
      _az(az)
{
    _method = &TransformManager::rotateObject;
}

void RotateModels::execute()
{
    (*(_transforManager).*_method)(_objects, _ax, _ay, _az);
}



TransformModels::TransformModels(const std::shared_ptr<BaseObject> objects, std::shared_ptr<BaseTransformer> &transformer)
    : _objects(objects),
      _transformer(transformer)
{
    _method = &TransformManager::transformObject;
}

void TransformModels::execute()
{
    (*(_transforManager).*_method)(_objects, _transformer);
}
