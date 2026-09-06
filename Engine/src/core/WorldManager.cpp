#include <DTEngine/WorldManager.hpp>

#include <DTEngine/GameObject.hpp>
#include <DTEngine/World.hpp>

#include "system/SystemRegistry.hpp"
#include "system/WorldSystem.hpp"

using namespace DTEngine;

int WorldManager::RegisterWorld(const std::string& name, std::function<void()> startFunction, bool defaultObjects)
{
    return SystemRegistry::GetSystem<WorldSystem>()->RegisterWorld(name, startFunction, defaultObjects);
}

void WorldManager::LoadWorld(int index)
{
    return SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(index);
}

void WorldManager::LoadWorld(const std::string& name)
{
    return SystemRegistry::GetSystem<WorldSystem>()->LoadWorld(name);
}

EntityHandle<GameObject> WorldManager::Instantiate(const std::string& name)
{
    return SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Instantiate(name);
}

void WorldManager::Destroy(const EntityHandle<GameObject>& object)
{
    SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Destroy(object);
}

void WorldManager::Destroy(GameObject& object)
{
    SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Destroy(object);
}

void WorldManager::Destroy(GameObject* object)
{
    SystemRegistry::GetSystem<WorldSystem>()->GetActiveWorld()->Destroy(object);
}