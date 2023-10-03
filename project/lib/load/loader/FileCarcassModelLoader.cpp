#include "FileCarcassModelLoader.h"
#include "Exceptions.h"
#include <source_location>

FileCarcassModelLoader::FileCarcassModelLoader()
{
    _file = std::make_shared<std::ifstream>();
}

FileCarcassModelLoader::FileCarcassModelLoader(std::shared_ptr<std::ifstream> &file)
{
    _file = file;
}

void FileCarcassModelLoader::open(std::string &fileName)
{
    if (!_file)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "File not open error");
    }

    _file->open(fileName);

    if (!_file)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "File not open error");
    }
}

void FileCarcassModelLoader::close()
{
    if (!_file)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "File not open error");
    }

    _file->close();
}

std::size_t FileCarcassModelLoader::loadCount()
{
    int count;

    *_file >> count;

    return count;
}

Vertex FileCarcassModelLoader::loadVertex()
{
    double x, y, z;

    *_file >> x >> y >> z;

    return Vertex(x, y, z);
}

std::vector<Vertex> FileCarcassModelLoader::loadVertices()
{
    std::vector<Vertex> vertexes;

    int vertexNum;
    *_file >> vertexNum;

    if (vertexNum <= 0)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "Wrong vertex number error");
    }

    double x, y, z;

    for (int i = 0; i < vertexNum; i++)
    {
       *_file >> x >> y >> z;
       vertexes.emplace_back(x, y, z);
    }

    return vertexes;
}

std::vector<Edge> FileCarcassModelLoader::loadEdges(int &vertex_amount)
{
    std::vector<Edge> links;

    int links_amount;
    *_file >> links_amount;

    if (links_amount <= 0)
    {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "Wrong links amount error");
    }

    int ivertex_start, ivertex_end;

    for (int i = 0; i < links_amount; i++)
    {
        *_file >> ivertex_start >> ivertex_end;

        if (ivertex_start <= 0 or ivertex_end <= 0 or
            ivertex_start > vertex_amount or ivertex_end > vertex_amount)
        {
        auto loc = std::source_location::current();
        throw SourceException(loc.file_name(), loc.function_name(), loc.line(), "Wrong link data error");
        }

        links.emplace_back(ivertex_start, ivertex_end);
    }

    return links;
}
