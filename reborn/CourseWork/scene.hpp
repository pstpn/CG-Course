#pragma once

#include "model.hpp"


class Scene {
public:
    std::vector<Model> objects;

    void addObject(const Model& obj)
    {
        objects.push_back(obj);
    }

    void render(Shader& shaders)
    {
        for (auto& obj : objects)
            obj.Draw(shaders);
    }
};