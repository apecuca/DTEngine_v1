#ifndef DTENGINE_COMPONENT_H
#define DTENGINE_COMPONENT_H

#include <DTEngine/Entity.hpp>

namespace DTEngine
{

class GameObject;
struct Collision;

class Component : public Entity 
{
friend class GameObject;

public:
    virtual ~Component();
    Component(GameObject& _gameObject);

private:
    // Called before Start
    virtual void Awake() {}

    // Called before the first frame is rendered
    virtual void Start() {}

    // Called before every physics update, runs on a fixed timer
    virtual void FixedUpdate() {}

    // Main loop, called every frame
    virtual void Update() {}

    // Called every frame after Update
    virtual void LateUpdate() {}

    // Called the instant the component is marked for destruction (on RemoveComponent(c))
    virtual void OnMarkedForDestruction() {}

    // Called right before the component is destroyed
    virtual void OnDestroy() {}

    virtual void OnCollisionEnter(Collision& collision) {};
    virtual void OnCollisionStay(Collision& collision) {};
    virtual void OnCollisionExit(Collision& collision) {};

    virtual void OnSensorEnter(Collision& collision) {};
    virtual void OnSensorStay(Collision& collision) {};
    virtual void OnSensorExit(Collision& collision) {};

public:
    GameObject& gameObject;

};

}

#endif