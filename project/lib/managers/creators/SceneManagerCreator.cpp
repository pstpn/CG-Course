#include <SceneManagerCreator.h>

std::shared_ptr<SceneManager> SceneManagerCreator::createManager() {
    if (Manager == nullptr)
        createInstance();

    return Manager;
}


void SceneManagerCreator::createInstance()
{
    static std::shared_ptr<SceneManager> manager(new SceneManager());
    Manager = manager;
}
