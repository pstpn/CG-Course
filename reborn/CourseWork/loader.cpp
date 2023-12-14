#include "loader.hpp"


void Loader::loadModel(const char* path, Model& model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs |
        aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "Failed to import model file: " << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(scene->mRootNode, scene, model);
}

void Loader::processNode(aiNode* node, const aiScene* scene, Model& model)
{
    aiMesh* mesh = scene->mMeshes[0];
    model.meshes.push_back(processMesh(mesh, scene, model));
}

Mesh Loader::processMesh(aiMesh* mesh, const aiScene* scene, Model& model)
{
    Vertex vertex;
    Face face;
    glm::vec3 pos, normal, velocity;

    aiFace aiFace;

    unsigned int i, j;

    for (i = 0; i < mesh->mNumVertices; ++i)
    {
        pos.x = mesh->mVertices[i].x;
        pos.y = mesh->mVertices[i].y;
        pos.z = mesh->mVertices[i].z;

        normal.x = mesh->mNormals[i].x;
        normal.y = mesh->mNormals[i].y;
        normal.z = mesh->mNormals[i].z;

        velocity.x = mesh->mNormals[i].x / 10000;
        velocity.y = mesh->mNormals[i].y / 10000;
        velocity.z = mesh->mNormals[i].z / 10000;

        vertex.Position = pos;
        vertex.Normal = normal;
        vertex.Velocity = velocity;

        model.vertices.push_back(vertex);
    }
    for (i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace = mesh->mFaces[i];
        for (j = 0; j < aiFace.mNumIndices; ++j)
            model.indices.push_back(aiFace.mIndices[j]);
    }
    for (i = 0; i < mesh->mNumFaces; i += 2)
    {
        face.Triangles.first = glm::uvec3(
            mesh->mFaces[i].mIndices[0],
            mesh->mFaces[i].mIndices[1],
            mesh->mFaces[i].mIndices[2]
        );

        face.Triangles.second = glm::uvec3(
            mesh->mFaces[i + 1].mIndices[0],
            mesh->mFaces[i + 1].mIndices[1],
            mesh->mFaces[i + 1].mIndices[2]
        );

        glm::vec3 faceVec1 = glm::vec3(
            model.vertices[face.Triangles.second.y].Position.x - model.vertices[face.Triangles.first.x].Position.x,
            model.vertices[face.Triangles.second.y].Position.y - model.vertices[face.Triangles.first.x].Position.y,
            model.vertices[face.Triangles.second.y].Position.z - model.vertices[face.Triangles.first.x].Position.z
        );

        glm::vec3 faceVec2 = glm::vec3(
            model.vertices[face.Triangles.second.z].Position.x - model.vertices[face.Triangles.first.x].Position.x,
            model.vertices[face.Triangles.second.z].Position.y - model.vertices[face.Triangles.first.x].Position.y,
            model.vertices[face.Triangles.second.z].Position.z - model.vertices[face.Triangles.first.x].Position.z
        );

        face.Normal = glm::normalize(glm::cross(faceVec1, faceVec2));

        model.faces.push_back(face);
    }

    model.toWorld();

    return Mesh(model.vertices, model.indices);
}