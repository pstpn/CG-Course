#include "TransformManagerCreator.h"


std::shared_ptr<TransformManager> TransformManagerCreator::createManager()
{
    if (Manager == nullptr)
        createInstance();

    return Manager;
}

void TransformManagerCreator::createInstance()
{
    static std::shared_ptr<TransformManager> manager(new TransformManager());
    Manager = manager;
}
