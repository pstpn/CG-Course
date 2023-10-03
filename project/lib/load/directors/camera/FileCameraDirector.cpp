#include "FileCameraDirector.h"
// #include "Exceptions.h"

std::shared_ptr<Camera> FileCameraDirector::load(std::shared_ptr<BaseCameraBuilder> builder, std::string &fileName)
{
    builder->open(fileName);

    builder->build();
    builder->buildLocation();

    builder->close();

    return builder->get();
}
