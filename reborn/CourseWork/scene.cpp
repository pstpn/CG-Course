#include "scene.hpp"
#include "model.hpp"
#include "sphere.hpp"

const float EPS = 9.5*1e-2;

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

void Scene::removeSphere(int index)
{
    if (index >= 0 && index < spheres.size())
        spheres.erase(spheres.begin() + index);
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

    for (unsigned int i = 0; i < spheres.size(); ++i)
        if (spheres[i]->getColor().w < EPS)
        {
            removeSphere(i--);
            std::cout << spheres.size() << std::endl;
        }
        else
            spheres[i]->Draw(shaders, glTime, *this);
}