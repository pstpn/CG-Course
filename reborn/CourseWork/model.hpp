#pragma once

#include "scene.hpp"
#include "loader.hpp"
#include "shader.hpp"
#include "mesh.hpp"


struct ModelSettings
{
    glm::mat4 modelMatrix;
    glm::vec4 color;
    bool lightingEnable;
    int inviseMode;
    float speed;
};

class Model
{
public:
    virtual ~Model() = default;

    glm::vec4 maxRoomVert = glm::mat4(1.0f) * (glm::vec4(1, 1, 1, 1) * 20.0f);
    glm::vec4 minRoomVert = glm::mat4(1.0f) * (glm::vec4(-1, -1, -1, 1) * 20.0f);

    virtual void Draw(Shader& shader, float& glTime, Scene& scene) = 0;

    virtual void setColor(glm::vec4& newColor) = 0;
    virtual void setModelMatrix(glm::mat4& modelMatrix) = 0;
    virtual void setSpeed(float& speed) = 0;

    virtual void pushMesh(const Mesh& mesh) = 0;
    virtual void pushIndex(const unsigned int& index) = 0;
    virtual void pushVertex(const Vertex& vertex) = 0;
    virtual void pushFace(const Face& face) = 0;

    virtual std::vector<unsigned int>& getIndices() = 0;
    virtual std::vector<Vertex>& getVertices() = 0;
    virtual std::vector<Face>& getFaces() = 0;
    virtual std::vector<Mesh>& getMeshes() = 0;
    virtual glm::mat4& getModelMatrix() = 0;
    virtual float getSpeed() = 0;
    virtual glm::vec4& getColor() = 0;

    virtual void toWorld() = 0;
};