#include "sphere.hpp"


const float EPSILON = 1e-4f;

void Sphere::Draw(Shader& shader, float& glTime, Scene& scene)
{
    shader.setVec4("modelColor", modelSettings.color);
    shader.setVec3("lightColor", (modelSettings.lightingEnable) ? 
        glm::vec3(1.0f, 1.0f, 1.0f) : 
        glm::vec3(0.0f, 0.0f, 0.0f));
    shader.setMat4("model", modelSettings.modelMatrix);
    glCullFace(modelSettings.inviseMode);

    unsigned int i;

    for (i = 0; i < meshes.size(); ++i)
    {
        meshes[i].Bind();
        updateVelocity(scene, glTime);
        meshes[i].Draw(shader);
        meshes[i].Unbind();
    }
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

void Sphere::toWorld()
{
    unsigned int i;

    for (i = 0; i < vertices.size(); ++i)
        vertices[i].Position = modelSettings.modelMatrix * glm::vec4(vertices[i].Position, 1);

    for (i = 0; i < faces.size(); ++i)
        faces[i].Normal = modelSettings.modelMatrix * glm::vec4(faces[i].Normal, 1);
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

bool Sphere::isIntersecting(
    const glm::vec3& orig,
    const glm::vec3& dir,
    const glm::vec3& tri0,
    const glm::vec3& tri1,
    const glm::vec3& tri2) 
{
    glm::vec3 edge1 = tri1 - tri0;
    glm::vec3 edge2 = tri2 - tri0;

    glm::vec3 h = glm::cross(dir, edge2);
    float a = glm::dot(edge1, h);

    if (a > -EPSILON && a < EPSILON)
        return false;

    float f = 1.0f / a;
    glm::vec3 s = orig - tri0;
    float u = f * glm::dot(s, h);

    if (u < 0.0f || u > 1.0f)
        return false;

    glm::vec3 q = glm::cross(s, edge1);
    float v = f * glm::dot(dir, q);

    if (v < 0.0f || u + v > 1.0f)
        return false;

    float t = f * glm::dot(edge2, q);

    return t > EPSILON;
}

void Sphere::updateVelocity(Scene& scene, float& glTime)
{
    Vertex* pData = (Vertex*) glMapBuffer(GL_ARRAY_BUFFER, GL_READ_WRITE);

    unsigned int i, j, k;

    glm::vec3 curPos, curVel, worldPoint;;

    std::vector<Model*> sceneObjects = scene.getObjects();
    std::vector<Face> objFaces;
    std::vector<Vertex> objVertices;

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
                objVertices = sceneObjects[j]->getVertices();
                objFaces = sceneObjects[j]->getFaces();

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
                    for (k = 0; k < 6; ++k)
                        if (isIntersecting(
                            glm::vec3(curPos),
                            glm::vec3(worldPoint),
                            glm::vec3(objVertices[objFaces[k].Triangles.first.x].Position),
                            glm::vec3(objVertices[objFaces[k].Triangles.first.y].Position),
                            glm::vec3(objVertices[objFaces[k].Triangles.first.z].Position)) ||
                            isIntersecting(
                                glm::vec3(curPos),
                                glm::vec3(worldPoint),
                                glm::vec3(objVertices[objFaces[k].Triangles.second.x].Position),
                                glm::vec3(objVertices[objFaces[k].Triangles.second.y].Position),
                                glm::vec3(objVertices[objFaces[k].Triangles.second.z].Position)))
                        {
                            curVel -= 2 * glm::dot(curVel, objFaces[k].Normal) * objFaces[k].Normal;
                            break;
                        }
            }

        pData[i].Velocity = curVel;
        vertices[i].Velocity = curVel;

        pData[i].Position = curPos + curVel * glTime;
        vertices[i].Position = curPos + curVel * glTime;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}