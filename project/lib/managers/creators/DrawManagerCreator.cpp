#include <DrawManagerCreator.h>


std::shared_ptr<DrawManager> DrawManagerCreator::createManager()
{
    if (Manager == nullptr)
        createInstance();

    return Manager;
}


void DrawManagerCreator::createInstance()
{
    static std::shared_ptr<DrawManager> manager(new DrawManager());
    Manager = manager;
}
