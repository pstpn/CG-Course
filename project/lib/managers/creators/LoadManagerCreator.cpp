#include <LoadManagerCreator.h>

std::shared_ptr<LoadManager> LoadManagerCreator::createManager()
{
    if (Manager == nullptr)
        createInstance();

    return Manager;
}

void LoadManagerCreator::createInstance()
{
    static std::shared_ptr<LoadManager> manager(new LoadManager());

    Manager = manager;
}
