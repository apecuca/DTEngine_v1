#include <Component.hpp>

#include "GameObject.hpp"

using namespace DTEngine;

Component::~Component()
{
    //
}

Component::Component(GameObject& _gameObject) :
    Entity(),
    gameObject(_gameObject)
{
    //
}