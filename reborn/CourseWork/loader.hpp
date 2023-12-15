#pragma once

#include "mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>


class Model;

class Loader
{
public:
    void loadModel(const std::string& path, Model& model);

private:
    std::string directory;

    void processNode(aiNode* node, const aiScene* scene, Model& model);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, Model& model);
};