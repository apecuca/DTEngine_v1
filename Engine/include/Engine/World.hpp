#ifndef INCLUDED_WORLD_H
#define INCLUDED_WORLD_H

#include <memory>

#include "Engine/GameObject.hpp"

namespace DTEngine
{

class World final  : public GameObject
{
public:
    ~World();
    World();

    // Instantiated a new object in the world
    GameObject* Instantiate();

    // Destroys an object instantiated in the world
    void Destroy(const GameObject* obj);

    // Processes the destruction queue, don't call this manually
    void ProcessDestroyQueue();

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;

};

}

#endif