#include <GameObject.hpp>

using namespace DTEngine;

GameObject::~GameObject()
{
    //
}

GameObject::GameObject() :
    Entity()
{
    //
}

void GameObject::MarkForDestruction()
{
    markedForDestruction = true;
}

bool GameObject::GetMarkedForDestruction() const
{
    return markedForDestruction;
}