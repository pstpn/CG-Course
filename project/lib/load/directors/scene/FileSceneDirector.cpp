#include "FileSceneDirector.h"
#include "FileCameraDirector.h"
#include "LoadModelDirector.h"
#include "Exceptions.h"

std::shared_ptr<Scene> FileSceneDirector::load(std::shared_ptr<SceneBuilder> builder, std::string &filename)
{
    builder->build();
    builder->open(filename);

    loadModels(builder, filename);
    loadCameras(builder, filename);

    builder->close();
    return builder->get();
}

void FileSceneDirector::loadModels(std::shared_ptr<SceneBuilder> builder, std::string &filename)
{
    size_t modelsAmount = builder->buildCount();

    auto modelBuilder = std::make_shared<ModelBuilder>();

    for (size_t i = 0; i < modelsAmount; ++i)
    {
        auto model = LoadModelDirector().load(modelBuilder, filename);
        builder->buildObject(model);
    }
}

void FileSceneDirector::loadCameras(std::shared_ptr<SceneBuilder> builder, std::string &filename)
{
    size_t camerasAmount = builder->buildCount();

    auto cameraBuilder = std::make_shared<CameraBuilder>();

    for (size_t i = 0; i < camerasAmount; ++i)
    {
        auto camera = FileCameraDirector().load(cameraBuilder, filename);
        builder->buildObject(camera);
    }
}
