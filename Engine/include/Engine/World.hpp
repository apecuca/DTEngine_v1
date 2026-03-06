#ifndef DTENGINE_WORLD_H
#define DTENGINE_WORLD_H

#include <memory>

#include "Engine/GameObject.hpp"

namespace DTEngine
{

class World final  : public GameObject
{
friend class Engine;

public:
    ~World();
    World();

    // Instantiated a new object in the world
    GameObject* Instantiate();

    // Destroys an object instantiated in the world
    void Destroy(const GameObject* obj);

private:
    // Processes the destruction queue
    void ProcessDestroyQueue();

    void WorldStart();
    void WorldUpdate();

private:
    std::vector<std::unique_ptr<GameObject>> gameObjects;
};

}

#endif