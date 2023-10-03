#include <QDebug>

#include "ModelAction.h"


TranslateModel::TranslateModel(const std::shared_ptr<BaseObject> object, const double dx, const double dy, const double dz)
    : _object(object),
      _dx(dx),
      _dy(dy),
      _dz(dz)
{
    _method = &TransformManager::translateObject;
}

void TranslateModel::execute()
{
    (*(_transforManager).*_method)(_object, _dx, _dy, _dz);
}



ScaleModel::ScaleModel(const std::shared_ptr<BaseObject> object, const double kx, const double ky, const double kz)
    : _object(object),
      _kx(kx),
      _ky(ky),
      _kz(kz)
{
    _method = &TransformManager::scaleObject;
}

void ScaleModel::execute()
{
    (*(_transforManager).*_method)(_object, _kx, _ky, _kz);
}



RotateModel::RotateModel(const std::shared_ptr<BaseObject> object, const double ax, const double ay, const double az)
    : _object(object),
      _ax(ax),
      _ay(ay),
      _az(az)
{
    _method = &TransformManager::rotateObject;
}

void RotateModel::execute()
{
    (*(_transforManager).*_method)(_object, _ax, _ay, _az);
}



TransformModel::TransformModel(const std::shared_ptr<BaseObject> object, std::shared_ptr<BaseTransformer> &transformer)
    : _object(object),
      _transformer(transformer)
{
    _method = &TransformManager::transformObject;
}

void TransformModel::execute()
{
    (*(_transforManager).*_method)(_object, _transformer);
}



RemoveModel::RemoveModel(const std::size_t id) : _id(id)
{
    _method = &SceneManager::retranslateObject;
}

void RemoveModel::execute()
{
    (*(_sceneManager).*_method)(_id);
}



AddModel::AddModel(ID &id, std::shared_ptr<BaseObject> object)
    : _object(object),
      _id(id)
{
    _method = &SceneManager::addObject;
}

void AddModel::execute()
{
    (*_id) = (*(_sceneManager).*_method)(_object);
}



LoadModel::LoadModel(std::shared_ptr<BaseObject> &object, std::string &filename)
    : _object(object),
      _filename(filename)
{
    _method = &LoadManager::load;
}

void LoadModel::execute()
{
    _object = (*(_loadManager).*_method)(_filename);
}
