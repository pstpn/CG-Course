#pragma once

#include <cstddef>
#include <memory>

#include "BaseAction.h"

using ID = std::shared_ptr<std::size_t>;

class ModelAction : public BaseAction { };

class TranslateModel : public ModelAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &dx, const double &dy, const double &dz);
public:
    TranslateModel(const std::shared_ptr<BaseObject> object, const double dx, const double dy, const double dz);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _object;
    double _dx, _dy, _dz;
    Action _method;
};


class ScaleModel : public ModelAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &kx, const double &ky, const double &kz);
public:
    ScaleModel(const std::shared_ptr<BaseObject> object, const double kx, const double ky, const double kz);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _object;
    double _kx, _ky, _kz;
    Action _method;
};



class RotateModel : public ModelAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, const double &ox, const double &oy, const double &oz);
public:
    RotateModel(const std::shared_ptr<BaseObject> object, const double ax, const double ay, const double az);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _object;
    double _ax, _ay, _az;
    Action _method;
};



class TransformModel : public ModelAction
{
    using Action = void(TransformManager::*)(const std::shared_ptr<BaseObject> &object, std::shared_ptr<BaseTransformer> &transformer);
public:
    TransformModel(const std::shared_ptr<BaseObject> object, std::shared_ptr<BaseTransformer> &transformer);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> _object;
    std::shared_ptr<BaseTransformer> _transformer;
    Action _method;
};



class RemoveModel : public ModelAction
{
    using Action = void(SceneManager::*)(const size_t id);
public:
    RemoveModel(const std::size_t id);

    virtual void execute() override;

private:
    std::size_t _id;
    Action _method;
};

class AddModel: public ModelAction
{
    using Action = std::size_t(SceneManager::*)(const shared_ptr<BaseObject> &object);
public:
    AddModel(ID &id, shared_ptr<BaseObject> object);

    virtual void execute() override;
private:
    ID &_id;
    std::shared_ptr<BaseObject> _object;

    Action _method;
};

class LoadModel : public ModelAction
{
    using Action = std::shared_ptr<BaseObject>(LoadManager::*)(std::string &name);
public:
    LoadModel(std::shared_ptr<BaseObject> &object, std::string &fileName);

    virtual void execute() override;

private:
    std::shared_ptr<BaseObject> &_object;
    std::string _filename;

    Action _method;
};
