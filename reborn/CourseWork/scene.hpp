#pragma once

#include "model.hpp"


class Scene
{
public:
    void addObject(const Model& obj)
    {
        objects.push_back(obj);
    }

    void render(Shader& shaders, float& glTime)
    {
        for (auto& obj : objects)
            obj.Draw(shaders, glTime, *this);
    }

    std::vector<Model> getObjects()
    {
        return objects;
    }

private:
    // lighting
    glm::vec3 lightPos;

    // Scene objects
    std::vector<Model> objects;
};