#include "obstacle.hpp"


void Obstacle::Draw(Shader& shader, float& glTime, Scene& scene)
{
    unsigned int i;

    for (i = 0; i < meshes.size(); ++i)
    {
        meshes[i].Bind();
        meshes[i].Draw(shader);
        meshes[i].Unbind();
    }
}

void Obstacle::toWorld()
{
    unsigned int i, j;

    for (i = 0; i < vertices.size(); ++i)
        vertices[i].Position = modelMatrix * glm::vec4(vertices[i].Position, 1);

    for (i = 0; i < faces.size(); ++i)
        faces[i].Normal = modelMatrix * glm::vec4(faces[i].Normal, 1);
}
