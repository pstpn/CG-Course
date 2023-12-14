#pragma once

#include "model.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>


class Loader
{
public:
    void loadModel(const char* path, Model& model);

private:
    void processNode(aiNode* node, const aiScene* scene, Model& model);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, Model& model);
};