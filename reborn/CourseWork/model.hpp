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
    std::vector<unsigned int> indices;

    Model(const char* path)
    {
        loadModel(path);
    }
    void Draw(Shader& shader, bool updateVel=false);
    void updateVelocity();
private:
    glm::vec4
        maxRoomVert = glm::mat4(1.0f) * glm::vec4(1, 1, 1, 1),
        minRoomVert = glm::mat4(1.0f) * glm::vec4(-1, -1, -1, 1);

    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    bool isInsideRoom(glm::vec4& point);
    glm::vec3 getNormal(glm::vec3& point);
};