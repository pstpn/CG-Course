#include "scene.hpp"
#include "model.hpp"
#include "sphere.hpp"


void Scene::addObject(Model& obj)
{
    objects.push_back(&obj);
}

void Scene::addObject(Model* obj)
{
    objects.push_back(obj);
}

void Scene::removeObject(int index)
{
    if (index >= 0 && index < objects.size())
        objects.erase(objects.begin() + index);
}

std::vector<Model*>& Scene::getObjects()
{
    return objects;
}

void Scene::updateObjectColor(glm::vec4& newColor, int& modelIndex)
{
    objects[modelIndex]->setColor(newColor);
}

glm::vec4 Scene::getObjectColor(int& modelIndex)
{
    return objects[modelIndex]->getColor();
}

void Scene::addSphere(Model& sphere)
{
    spheres.push_back(&sphere);
}

void Scene::addSphere(Model* sphere)
{
    spheres.push_back(sphere);
}

void Scene::render(Shader& shaders, float& glTime)
{
    for (auto& obj : objects)
        obj->Draw(shaders, glTime, *this);

    for (auto& sphere : spheres)
        sphere->Draw(shaders, glTime, *this);
}