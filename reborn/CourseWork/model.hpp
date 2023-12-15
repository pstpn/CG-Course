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
};

class Model
{
public:
    glm::vec4 maxRoomVert = glm::mat4(1.0f) * (glm::vec4(1, 1, 1, 1) * 10.0f);
    glm::vec4 minRoomVert = glm::mat4(1.0f) * (glm::vec4(-1, -1, -1, 1) * 10.0f);

    virtual void Draw(Shader& shader, float& glTime, Scene& scene) = 0;

    virtual void pushMesh(const Mesh& mesh) = 0;
    virtual void pushIndex(const unsigned int& index) = 0;
    virtual void pushVertex(const Vertex& vertex) = 0;
    virtual void pushFace(const Face& face) = 0;

    virtual std::vector<unsigned int>& getIndices() = 0;
    virtual std::vector<Vertex>& getVertices() = 0;
    virtual std::vector<Face>& getFaces() = 0;

    virtual void toWorld() = 0;
};