#pragma once

#include "shader.hpp"


class Model;

class Scene
{
public:
    void addObject(Model& obj);
    void addObject(Model* obj);
    void render(Shader& shaders, float& glTime);
    std::vector<Model*>& getObjects();

private:
    // lighting
    glm::vec3 lightPos;

    // Scene objects
    std::vector<Model*> objects;
};