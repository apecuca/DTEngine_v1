#include "system/WorldSystem.hpp"

#include <DTEngine/World.hpp>
#include "system/SystemRegistry.hpp"
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/Camera.hpp>

using namespace DTEngine;

WorldSystem::~WorldSystem()
{
    //
}

WorldSystem::WorldSystem()
{
    //
}

bool WorldSystem::Init()
{
    return true;
}

World* WorldSystem::GetActiveWorld()
{
    return activeWorld == nullptr ? nullptr : activeWorld.get();
}

bool WorldSystem::IsWorldActive()
{
    if (activeWorld == nullptr) return false;

    return true;
}

int WorldSystem::RegisterWorld(std::string name, std::function<void()> startFunction, bool defaultObjects)
{
    if (GetWorldIndex(name) != -1)
        throw std::runtime_error("World " + name + " was already registered");

    registeredWorlds.emplace_back(name, defaultObjects, startFunction);

    return static_cast<int>(registeredWorlds.size() - 1);
}

void WorldSystem::LoadWorld(int index)
{
    if (index < 0 || index >= registeredWorlds.size())
        throw std::runtime_error("World index " + std::to_string(index) + " out of bounds");

    // Defer the actual swap to a safe point (OnEndOfFrame). Performing it here
    // would destroy the world while it may still be mid-update, freeing the
    // very component/object that requested the load (use-after-free)
    pendingWorldIndex = index;
    worldLoadPending = true;
}

void WorldSystem::LoadWorld(const std::string& name)
{
    int worldIndex = GetWorldIndex(name);
    if (worldIndex == -1)
        throw std::runtime_error("World " + name + " isn't registered");

    LoadWorld(worldIndex);
}

void WorldSystem::ProcessWorldLoad()
{
    if (!worldLoadPending) return;

    int index = pendingWorldIndex;
    worldLoadPending = false;
    pendingWorldIndex = -1;

    WorldBlueprint& bp = registeredWorlds.at(index);

    activeWorld.reset();
    activeWorld = std::make_unique<World>(bp.name);

    if (bp.defaultObjects) {
        auto cam = activeWorld->Instantiate("Camera");
        cam->AddComponent<Camera>();
    }

    bp.startFunction();
}

int WorldSystem::GetWorldIndex(std::string name)
{
    for (int i = 0; i < registeredWorlds.size(); i++) {
        if (registeredWorlds.at(i).name == name)
            return i;
    }

    return -1;
}

void WorldSystem::UpdateActiveWorld()
{
    activeWorld->WorldUpdate();
}

void WorldSystem::FixedUpdateActiveWorld()
{
    activeWorld->WorldFixedUpdate();
}

void WorldSystem::OnEndOfFrame()
{
    // Apply a pending world swap here, after the frame's updates have unwound.
    // The old world is being discarded, so there's no need to process its
    // destroy queue.
    if (worldLoadPending) {
        ProcessWorldLoad();
        return;
    }

    activeWorld->ProcessDestroyQueue();
}