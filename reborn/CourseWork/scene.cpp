#include "scene.hpp"
#include "model.hpp"


void Scene::addObject(Model& obj)
{
    objects.push_back(&obj);
}

void Scene::addObject(Model* obj)
{
    objects.push_back(obj);
}

void Scene::render(Shader& shaders, float& glTime)
{
    for (auto& obj : objects)
        obj->Draw(shaders, glTime, *this);
}

std::vector<Model*>& Scene::getObjects()
{
    return objects;
}