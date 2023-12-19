#include "sphere.hpp"


const float EPSILON = 1e-4f;

void Sphere::Draw(Shader& shader, float& glTime, Scene& scene)
{
    shader.setVec4("modelColor", modelSettings.color);
    shader.setMat4("model", modelSettings.modelMatrix);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    unsigned int i;

    for (i = 0; i < meshes.size(); ++i)
    {
        meshes[i].Bind();
        updateVelocity(scene, glTime);
        meshes[i].Draw(shader);
        meshes[i].Unbind();
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Sphere::setColor(glm::vec4& newColor)
{
    modelSettings.color = newColor;
}

void Sphere::setModelMatrix(glm::mat4& modelMatrix)
{
    modelSettings.modelMatrix = modelMatrix;
}

void Sphere::setSpeed(float& speed)
{
    modelSettings.speed = speed;
}

void Sphere::pushMesh(const Mesh& mesh)
{
    meshes.push_back(mesh);
}

void Sphere::pushIndex(const unsigned int& index)
{
    indices.push_back(index);
}

void Sphere::pushVertex(const Vertex& vertex)
{
    vertices.push_back(vertex);
}

void Sphere::pushFace(const Face& face)
{
    faces.push_back(face);
}

std::vector<unsigned int>& Sphere::getIndices()
{
    return indices;
}

std::vector<Vertex>& Sphere::getVertices()
{
    return vertices;
}

std::vector<Face>& Sphere::getFaces()
{
    return faces;
}

std::vector<Mesh>& Sphere::getMeshes()
{
    return meshes;
}

glm::mat4& Sphere::getModelMatrix()
{
    return modelSettings.modelMatrix;
}

float Sphere::getSpeed()
{
    return modelSettings.speed;
}

glm::vec4& Sphere::getColor()
{
    return modelSettings.color;
}

void Sphere::toWorld()
{
    glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(modelSettings.modelMatrix)));

    unsigned int i;

    for (i = 0; i < vertices.size(); ++i)
        vertices[i].Position = modelSettings.modelMatrix * glm::vec4(vertices[i].Position, 1);
}

bool Sphere::isInsideRoom(glm::vec3& point)
{
    return
        point.x < maxRoomVert.x &&
        point.x > minRoomVert.x &&
        point.y < maxRoomVert.y &&
        point.y > minRoomVert.y &&
        point.z < maxRoomVert.z &&
        point.z > minRoomVert.z;
}

void Sphere::updateVelocity(Scene& scene, float& glTime)
{
    unsigned int i, j, k;
    float t = 1;

    glm::vec3 curPos, curVel, normal, worldPoint;

    std::vector<Model*> sceneObjects = scene.getObjects();

    for (i = 0; i < vertices.size(); ++i)
    {
        curVel = vertices[i].Velocity;
        curPos = vertices[i].Position;
        worldPoint = curPos + curVel * glTime;

        if (!isInsideRoom(worldPoint))
        {
            if (worldPoint.x < minRoomVert.x || worldPoint.x > maxRoomVert.x)
                curVel.x = -curVel.x;
            if (worldPoint.y < minRoomVert.y || worldPoint.y > maxRoomVert.y)
                curVel.y = -curVel.y;
            if (worldPoint.z < minRoomVert.z || worldPoint.z > maxRoomVert.z)
                curVel.z = -curVel.z;
        }
        else
            for (j = 0; j < sceneObjects.size(); ++j)
            {
                std::vector<Vertex>& objVertices = sceneObjects[j]->getVertices();
                std::vector<Face>& objFaces = sceneObjects[j]->getFaces();

                glm::vec3 pointToVertex0 = worldPoint - objVertices[objFaces[0].Triangles.first.z].Position;
                glm::vec3 pointToVertex1 = worldPoint - objVertices[objFaces[1].Triangles.first.z].Position;
                glm::vec3 pointToVertex2 = worldPoint - objVertices[objFaces[2].Triangles.first.z].Position;
                glm::vec3 pointToVertex3 = worldPoint - objVertices[objFaces[3].Triangles.first.z].Position;
                glm::vec3 pointToVertex4 = worldPoint - objVertices[objFaces[4].Triangles.first.z].Position;
                glm::vec3 pointToVertex5 = worldPoint - objVertices[objFaces[5].Triangles.first.z].Position;

                float pointPlane0 = glm::dot(pointToVertex0, objFaces[0].Normal);
                float pointPlane1 = glm::dot(pointToVertex1, objFaces[1].Normal);
                float pointPlane2 = glm::dot(pointToVertex2, objFaces[2].Normal);
                float pointPlane3 = glm::dot(pointToVertex3, objFaces[3].Normal);
                float pointPlane4 = glm::dot(pointToVertex4, objFaces[4].Normal);
                float pointPlane5 = glm::dot(pointToVertex5, objFaces[5].Normal);

                if (pointPlane0 < 0 && pointPlane1 < 0 && pointPlane2 < 0 && pointPlane3 < 0 && pointPlane4 < 0 && pointPlane5 < 0)
                {
                    vertices[i].Position = glm::vec3(INT_MAX);
                    curVel = glm::vec3(0.0f);
                    break;
                }
            }

        vertices[i].Velocity = curVel;
        vertices[i].Position += curVel * glTime;
    }

    for (const auto& face : faces)
    {
        float factor = 3;
        if (
            glm::distance(vertices[face.Triangles.first.x].Position, vertices[face.Triangles.first.y].Position) > factor ||
            glm::distance(vertices[face.Triangles.first.x].Position, vertices[face.Triangles.first.z].Position) > factor ||
            glm::distance(vertices[face.Triangles.first.y].Position, vertices[face.Triangles.first.z].Position) > factor
            )
        {
            vertices[face.Triangles.first.x].Position = glm::vec3(INT_MAX);
            vertices[face.Triangles.first.y].Position = glm::vec3(INT_MAX);
            vertices[face.Triangles.first.z].Position = glm::vec3(INT_MAX);
        }
        if (
            glm::distance(vertices[face.Triangles.second.x].Position, vertices[face.Triangles.second.y].Position) > factor ||
            glm::distance(vertices[face.Triangles.second.x].Position, vertices[face.Triangles.second.z].Position) > factor ||
            glm::distance(vertices[face.Triangles.second.y].Position, vertices[face.Triangles.second.z].Position) > factor
            )
        {
            vertices[face.Triangles.second.x].Position = glm::vec3(INT_MAX);
            vertices[face.Triangles.second.y].Position = glm::vec3(INT_MAX);
            vertices[face.Triangles.second.z].Position = glm::vec3(INT_MAX);
        }
    }

    Vertex* pData = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    memcpy(pData, &vertices[0], vertices.size() * sizeof(Vertex));

    glUnmapBuffer(GL_ARRAY_BUFFER);
}