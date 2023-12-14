#pragma once

#include "scene.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "mesh.hpp"


class Obstacle : public Model
{
public:
    glm::mat4 modelMatrix;

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    std::vector<Mesh> meshes;

    Obstacle() : modelMatrix(1.0f) {};
    Obstacle(glm::mat4& modelMatrix) : modelMatrix(modelMatrix) {};

    void Draw(Shader& shader, float& glTime, Scene& scene);

    void toWorld();
};