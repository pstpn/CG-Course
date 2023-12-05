#include "shader.hpp"

#include <glm/glm.hpp>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Velocity;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);
    void Draw(Shader& shader);
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
