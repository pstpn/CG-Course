#pragma once

#include <memory>

template<typename Tcreator>
class MediatorSolution
{
public:
    decltype(auto) create();
};

template<typename Tcreator>
decltype(auto) MediatorSolution<Tcreator>::create()
{
    auto creator = Tcreator();
    auto mediator = creator.createMediator();

    return mediator;
}
