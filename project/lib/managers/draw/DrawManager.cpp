#include <DrawManager.h>
#include <BaseModel.h>
#include <Camera.h>

void DrawManager::setAdapter(std::shared_ptr<DrawCompositeAdapter> adapter)
{
    _adapter = adapter;
}

void DrawManager::setCamera(std::shared_ptr<Camera> camera)
{
    _adapter->setCamera(camera);
}

void DrawManager::clearScene(std::shared_ptr<BaseDrawer> drawer)
{
    drawer->clearScene();
}

void DrawManager::drawScene(std::shared_ptr<Scene> scene, std::shared_ptr<BaseDrawer> drawer)
{
    _adapter->setDrawer(drawer);
    _adapter->setAdaptee(std::dynamic_pointer_cast<Composite>(scene->getObjects()));
    _adapter->request();
}
