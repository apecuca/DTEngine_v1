#include <World.hpp>

#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PoolSystem.hpp"

#include <algorithm>

using namespace DTEngine;

World::~World()
{
    // Objects live in the global pool; release them with their world
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    if (pool == nullptr)
        return;

    for (auto& ref : objectRefs)
        if (ref.IsAlive())
            pool->Release(ref.ptr);
}

World::World(std::string _name) :
    GameObject(_name)
{
    //
}

EntityHandle<GameObject> World::Instantiate(const std::string name)
{
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();

    EntitySlotRef ref = pool->Acquire(std::make_unique<GameObject>(name));
    objectRefs.emplace_back(ref);
    pendingAwake.emplace_back(ref);
    pendingStart.emplace_back(ref);

    return EntityHandle<GameObject>(ref);
}

void World::Destroy(const EntityHandle<GameObject>& obj)
{
    Destroy(obj.Get());
}

void World::Destroy(GameObject& obj)
{
    Destroy(&obj);
}

void World::Destroy(GameObject* obj)
{
    if (obj == nullptr)
        return;

    for (auto& ref : objectRefs) {
        if (!ref.IsAlive()) continue;

        if (ref.ptr == obj)
            static_cast<GameObject*>(ref.ptr)->MarkForDestruction();
    }
}

void World::ProcessDestroyQueue()
{
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    if (pool == nullptr)
        return;

    // Release marked components before their owners so the component
    // slots are returned to the pool as well
    for (auto& ref : objectRefs)
        if (ref.IsAlive())
            static_cast<GameObject*>(ref.ptr)->ProcessComponentDestructionQueue();

    for (auto& ref : objectRefs) {
        if (!ref.IsAlive()) continue;

        GameObject* gameObject = static_cast<GameObject*>(ref.ptr);
        if (gameObject->markedForDestruction)
            pool->Release(gameObject);
    }

    std::erase_if(objectRefs, [](const EntitySlotRef& ref) { return !ref.IsAlive(); });
}

void World::WorldAwake()
{
    if (pendingAwake.empty())
        return;

    // Copy to avoid changes mid passing
    std::vector<EntitySlotRef> vCopy = pendingAwake;
    pendingAwake.clear();

    for (auto& ref : vCopy)
        if (ref.IsLive())
            static_cast<GameObject*>(ref.ptr)->InternalAwake();

}

void World::WorldStart()
{
    if (pendingStart.empty())
        return;

    // Copy to avoid changes mid passing
    std::vector<EntitySlotRef> vCopy = pendingStart;
    pendingStart.clear();

    for (auto& ref : vCopy)
        if (ref.IsLive())
            static_cast<GameObject*>(ref.ptr)->InternalStart();
}

void World::WorldFixedUpdate()
{
    for (auto& ref : objectRefs)
        if (ref.IsLive())
            static_cast<GameObject*>(ref.ptr)->InternalFixedUpdate();
}

void World::WorldUpdate()
{
    // Call start/awake on unstarted/awaken objects
    WorldAwake();
    WorldStart();

    // Update behaviour
    // IsLive skips objects destroyed earlier in the current frame
    for (auto& ref : objectRefs)
        if (ref.IsLive())
            static_cast<GameObject*>(ref.ptr)->InternalUpdate();

    // Late update behaviour
    for (auto& ref : objectRefs)
        if (ref.IsLive())
            static_cast<GameObject*>(ref.ptr)->InternalLateUpdate();
}
