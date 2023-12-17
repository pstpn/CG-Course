#pragma once

#include "scene.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "mesh.hpp"


class Obstacle : public Model
{
public:
    ModelSettings modelSettings;

    std::vector<unsigned int> indices;
    std::vector<Vertex> vertices;
    std::vector<Face> faces;

    std::vector<Mesh> meshes;

    Obstacle(glm::mat4& modelMatrix, glm::vec4& modelColor, int inviseMode, bool lightingEnable=true)
    {
        modelSettings.modelMatrix = modelMatrix;
        modelSettings.color = modelColor;
        modelSettings.lightingEnable = lightingEnable;
        modelSettings.inviseMode = inviseMode;
    };
    ~Obstacle() = default;

    void Draw(Shader& shader, float& glTime, Scene& scene);

    void setColor(glm::vec4& newColor);
    glm::vec4& getColor();

    void pushMesh(const Mesh& mesh);
    void pushIndex(const unsigned int& index);
    void pushVertex(const Vertex& vertex);
    void pushFace(const Face& face);

    std::vector<unsigned int>& getIndices();
    std::vector<Vertex>& getVertices();
    std::vector<Face>& getFaces();
    float getSpeed();

    void toWorld();
};