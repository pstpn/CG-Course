#pragma once

#include "scene.hpp"
#include "loader.hpp"
#include "shader.hpp"
#include "mesh.hpp"


class Model
{
public:
    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    glm::vec4 maxRoomVert = glm::mat4(1.0f) * (glm::vec4(1, 1, 1, 1) * 10.0f);
    glm::vec4 minRoomVert = glm::mat4(1.0f) * (glm::vec4(-1, -1, -1, 1) * 10.0f);

    std::vector<Mesh> meshes;

    virtual void Draw(Shader& shader, float& glTime, Scene& scene) = 0;

    virtual void toWorld() = 0;
};
