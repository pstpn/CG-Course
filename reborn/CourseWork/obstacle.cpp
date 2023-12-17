#include "obstacle.hpp"


void Obstacle::Draw(Shader& shader, float& glTime, Scene& scene)
{
    shader.setVec4("modelColor", modelSettings.color);
    shader.setMat4("model", modelSettings.modelMatrix);
    glCullFace(modelSettings.inviseMode);

    unsigned int i;

    for (i = 0; i < meshes.size(); ++i)
    {
        meshes[i].Bind();
        meshes[i].Draw(shader);
        meshes[i].Unbind();
    }
}

void Obstacle::pushMesh(const Mesh& mesh)
{
    meshes.push_back(mesh);
}

void Obstacle::setColor(glm::vec4& newColor)
{
    modelSettings.color = newColor;
}

glm::vec4& Obstacle::getColor()
{
    return modelSettings.color;
}

void Obstacle::pushIndex(const unsigned int& index)
{
    indices.push_back(index);
}

void Obstacle::pushVertex(const Vertex& vertex)
{
    vertices.push_back(vertex);
}

void Obstacle::pushFace(const Face& face)
{
    faces.push_back(face);
}

std::vector<unsigned int>& Obstacle::getIndices()
{
    return indices;
}

std::vector<Vertex>& Obstacle::getVertices()
{
    return vertices;
}

std::vector<Face>& Obstacle::getFaces()
{
    return faces;
}

float Obstacle::getSpeed()
{
    return 0.0f;
}

void Obstacle::toWorld()
{
    unsigned int i;

    for (i = 0; i < vertices.size(); ++i)
        vertices[i].Position = modelSettings.modelMatrix * glm::vec4(vertices[i].Position, 1);

    for (i = 0; i < faces.size(); ++i)
        faces[i].Normal = modelSettings.modelMatrix * glm::vec4(faces[i].Normal, 1);
}