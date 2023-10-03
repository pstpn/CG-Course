#include <Edge.h>

Edge::Edge(const std::size_t start_point, const std::size_t end_point)
    : _start(start_point),
      _end(end_point)
{
}

std::size_t Edge::getStart() const
{
    return _start;
}

std::size_t Edge::getEnd() const
{
    return _end;
}

void Edge::setStart(const std::size_t index)
{
    _start = index;
}

void Edge::setEnd(const std::size_t index)
{
    _end = index;
}
