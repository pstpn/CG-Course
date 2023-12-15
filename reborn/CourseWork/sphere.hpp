#pragma once

#include "scene.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "mesh.hpp"


class Sphere : public Model
{
public:
    ModelSettings modelSettings;

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    std::vector<Mesh> meshes;

    Sphere(glm::mat4& modelMatrix, glm::vec4& modelColor, bool lightingEnable = true)
    {
        modelSettings.modelMatrix = modelMatrix;
        modelSettings.color = modelColor;
        modelSettings.lightingEnable = lightingEnable;
        modelSettings.inviseMode = GL_FRONT;
    };

    void Draw(Shader& shader, float& glTime, Scene& scene);

    void pushMesh(const Mesh& mesh);
    void pushIndex(const unsigned int& index);
    void pushVertex(const Vertex& vertex);
    void pushFace(const Face& face);

    std::vector<unsigned int>& getIndices();
    std::vector<Vertex>& getVertices();
    std::vector<Face>& getFaces();

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