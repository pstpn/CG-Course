#pragma once

#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>


struct Vertex 
{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 Velocity;
};

struct Face
{
    std::pair<glm::uvec3, glm::uvec3> Triangles;
    glm::vec3 Normal;
};

class Mesh {
public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;

    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

    void Bind();
    void Draw(Shader& shader);
    void Unbind();
private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
