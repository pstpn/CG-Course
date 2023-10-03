#include <QDebug>

#include "ModelLoadMediator.h"
#include "Exceptions.h"
#include "ModelBuilder.h"


ModelLoadMediator::ModelLoadMediator(std::shared_ptr<BaseModelDirector> director) :
    _builder(new ModelBuilder)
{
    _director = director;
}


std::shared_ptr<BaseObject> ModelLoadMediator::load(std::string &filename)
{
    std::shared_ptr<CarcassModel> modelPtr;

    try
    {
        modelPtr = _director->load(_builder, filename);
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

    return std::shared_ptr<BaseObject>(modelPtr);
}
