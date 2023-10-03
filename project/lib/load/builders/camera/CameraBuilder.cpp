#include "CameraBuilder.h"

CameraBuilder::CameraBuilder()
{
    _loader = std::make_shared<FileCarcassModelLoader>();
}

void CameraBuilder::open(std::string &fileName)
{
    _loader->open(fileName);
}

void CameraBuilder::close()
{
    _loader->close();
}

void CameraBuilder::build()
{
    _camera = std::make_shared<Camera>();
}

void CameraBuilder::buildLocation()
{
    Vertex location = _loader->loadVertex();
    Vertex direction = _loader->loadVertex();

    _camera = std::make_shared<Camera>(location, direction);
}

bool CameraBuilder::isBuild() const
{
    return _camera != nullptr;
}

std::shared_ptr<Camera> CameraBuilder::get()
{
    return _camera;
}
