#pragma once

#include "shader.hpp"


class Model;

class Sphere;

class Scene
{
public:
    ~Scene()
    {
        for (auto* object : objects)
            delete object;
        for (auto* sphere : spheres)
            delete sphere;

        objects.clear();
        spheres.clear();
    }

    void addObject(Model& obj);
    void addObject(Model* obj);
    void removeObject(int index);
    std::vector<Model*>& getObjects();

    void updateObjectColor(glm::vec4& newColor, int& modelIndex);
    glm::vec4 getObjectColor(int& modelIndex);

    void addSphere(Model& sphere);
    void addSphere(Model* sphere);

    void render(Shader& shaders, float& glTime);
private:
    // lighting
    glm::vec3 lightPos;

    // Scene objects
    std::vector<Model*> objects;
    std::vector<Model*> spheres;
};