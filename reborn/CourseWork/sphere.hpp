#pragma once

#include "scene.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "mesh.hpp"


class Sphere : public Model
{
public:
    glm::mat4 modelMatrix;

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;

    std::vector<Mesh> meshes;

    Sphere() : modelMatrix(1.0f) {};
    Sphere(glm::mat4& modelMatrix) : modelMatrix(modelMatrix) {};

    void Draw(Shader& shader, float& glTime, Scene& scene);

    void toWorld();

    bool isInsideRoom(glm::vec3& point);
    bool isIntersecting(
        const glm::vec3& orig,
        const glm::vec3& dir,
        const glm::vec3& tri0,
        const glm::vec3& tri1,
        const glm::vec3& tri2);
    void updateVelocity(Scene& scene, float& glTime);
};