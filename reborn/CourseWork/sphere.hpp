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

    Sphere(glm::mat4& modelMatrix, glm::vec4& modelColor, float& speed, bool lightingEnable = false)
    {
        modelSettings.modelMatrix = modelMatrix;
        modelSettings.color = modelColor;
        modelSettings.lightingEnable = lightingEnable;
        modelSettings.speed = speed;
    };
    Sphere(Model& sphere)
    {
        this->modelSettings.modelMatrix = sphere.getModelMatrix();
        this->modelSettings.color = sphere.getColor();
        this->modelSettings.lightingEnable = false;
        this->modelSettings.speed = sphere.getSpeed();

        for (auto& index : sphere.getIndices())
            this->indices.push_back(index);

        for (auto& vertex : sphere.getVertices())
            this->vertices.push_back(vertex);

        for (auto& face : sphere.getFaces())
            this->faces.push_back(face);

        for (auto& mesh : sphere.getMeshes())
        {
            mesh.setupMesh(*this);
            this->meshes.push_back(mesh);
        }
    }
    ~Sphere() = default;

    void Draw(Shader& shader, float& glTime, Scene& scene);

    void setColor(glm::vec4& newColor);
    void setModelMatrix(glm::mat4& modelMatrix);
    void setSpeed(float& speed);
    glm::vec4& getColor();

    void pushMesh(const Mesh& mesh);
    void pushIndex(const unsigned int& index);
    void pushVertex(const Vertex& vertex);
    void pushFace(const Face& face);

    std::vector<unsigned int>& getIndices();
    std::vector<Vertex>& getVertices();
    std::vector<Face>& getFaces();
    std::vector<Mesh>& getMeshes();
    glm::mat4& getModelMatrix();
    float getSpeed();

    void toWorld();

    bool isInsideRoom(glm::vec3& point);
    void updateVelocity(Scene& scene, float& glTime);
};