#ifndef DTENGINE_COMPONENT_H
#define DTENGINE_COMPONENT_H

#include "Entity.hpp"

namespace DTEngine
{

class GameObject;

class Component : public Entity 
{
public:
    virtual ~Component();
    Component(GameObject& _gameObject);

public:
    // Called before the first frame is rendered
    virtual void Start() {}

    // Main loop, called every frame
    virtual void Update() {}

public:
    GameObject& gameObject;

};

}

#endif