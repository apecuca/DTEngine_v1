#ifndef DTENGINE_WORLD_H
#define DTENGINE_WORLD_H

#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <vector>

namespace DTEngine
{

class World final  : public GameObject
{
friend class WorldSystem;

public:
    ~World();
    World();

    // Instantiated a new object in the world
    EntityHandle<GameObject> Instantiate();

    // Destroys an object instantiated in the world
    void Destroy(const EntityHandle<GameObject>& obj);

private:
    // Processes the destruction queue
    void ProcessDestroyQueue();

    void WorldAwake();
    void WorldStart();
    void WorldFixedUpdate();
    void WorldUpdate();

private:
    // References to this world's objects inside the PoolSystem
    std::vector<EntitySlotRef> objectRefs;

    // To be awoken
    std::vector<EntitySlotRef> pendingAwake;
    std::vector<EntitySlotRef> pendingStart;
};

}

#endif