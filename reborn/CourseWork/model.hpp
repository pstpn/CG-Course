#pragma once

#include "shader.hpp"
#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model
{
public:
    size_t vertexCount;
    std::vector<Vertex>       vertices;
    std::vector<Face>         faces;
    std::vector<unsigned int> indices;
    std::vector<Model> objects;
    std::vector<std::pair<bool, std::vector<float>>> prevNormalDots;

    void addObject(const Model& obj)
    {
        objects.push_back(obj);
        prevNormalDots.push_back(std::pair<bool, std::vector<float>>(false, std::vector<float>(6)));
    }

    Model(const char* path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader, bool updateVel=false);
    void updateVelocity();
private:
    glm::vec4
        maxRoomVert = glm::mat4(1.0f) * (glm::vec4(1, 1, 1, 1) * 10.0f),
        minRoomVert = glm::mat4(1.0f) * (glm::vec4(-1, -1, -1, 1) * 10.0f);

    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    bool isInsideRoom(glm::vec4& point);
    glm::vec3 getNormal(glm::vec3& point);
};