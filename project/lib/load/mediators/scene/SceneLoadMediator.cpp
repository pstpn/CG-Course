#include "SceneLoadMediator.h"
#include "Exceptions.h"
#include <source_location>

SceneLoadMediator::SceneLoadMediator(std::shared_ptr<BaseSceneDirector> director) :
    _builder(new SceneBuilder)
{
    _director = director;
}

std::shared_ptr<Scene> SceneLoadMediator::load(std::string &filename)
{
    std::shared_ptr<Scene> scene;

    try
    {
        scene = _director->load(_builder, filename);
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

    return scene;
}

void SceneLoadMediator::setDirector(std::shared_ptr<BaseSceneDirector> director)
{
    _director = director;
}
