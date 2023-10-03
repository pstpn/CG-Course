#include "CameraLoadMediator.h"
#include "Exceptions.h"
#include "CameraBuilder.h"


CameraLoadMediator::CameraLoadMediator(std::shared_ptr<BaseCameraDirector> director) :
    _builder(new CameraBuilder)
{
    _director = director;
}

std::shared_ptr<BaseObject> CameraLoadMediator::load(std::string &filename)
{
    std::shared_ptr<Camera> camera_sh_ptr;

    try
    {
        camera_sh_ptr = _director->load(_builder, filename);
    }
    catch (SourceException &error)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "File not open error");
    }
    catch (std::exception &error)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "Read model error");
    }

    return std::shared_ptr<BaseObject>(camera_sh_ptr);
}
