#include "system/SystemRegistry.hpp"

#include "system/WorldSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/PathSystem.hpp"
#include "system/TimeSystem.hpp"
#include "system/InputSystem.hpp"
#include "system/PhysicsSystem.hpp"
#include "system/PoolSystem.hpp"

#include <iostream>
#include <stdexcept>

using namespace DTEngine;

SystemRegistry* SystemRegistry::instance;

SystemRegistry::~SystemRegistry()
{
    if (instance == this)
        instance = nullptr;
}

SystemRegistry::SystemRegistry()
{
    if (instance != nullptr)
        throw std::runtime_error("SystemRegistry instance duplicate found");

    instance = this;
}

bool SystemRegistry::IsFullyWorking() const
{
    if (poolSystem == nullptr) return false;
    if (renderingSystem == nullptr) return false;
    if (worldSystem == nullptr) return false;
    if (pathSystem == nullptr) return false;
    if (timeSystem == nullptr) return false;
    if (inputSystem == nullptr) return false;
    if (physicsSystem == nullptr) return false;

    return true;
}

bool SystemRegistry::InitWorks(const std::string& assetsPath, const std::string& resourcesPath)
{
    pathSystem = std::make_unique<PathSystem>(assetsPath, resourcesPath);
    if (!pathSystem->Init()) return false;
    systems[typeid(PathSystem)] = pathSystem.get();

    poolSystem = std::make_unique<PoolSystem>();
    if (!poolSystem->Init()) return false;
    systems[typeid(PoolSystem)] = poolSystem.get();

    renderingSystem = std::make_unique<RenderingSystem>();
    if (!renderingSystem->Init()) return false;
    systems[typeid(RenderingSystem)] = renderingSystem.get();

    worldSystem = std::make_unique<WorldSystem>();
    if (!worldSystem->Init()) return false;
    systems[typeid(WorldSystem)] = worldSystem.get();

    timeSystem = std::make_unique<TimeSystem>();
    if (!timeSystem->Init()) return false;
    systems[typeid(TimeSystem)] = timeSystem.get();

    physicsSystem = std::make_unique<PhysicsSystem>();
    if (!physicsSystem->Init()) return false;
    systems[typeid(PhysicsSystem)] = physicsSystem.get();

    inputSystem = std::make_unique<InputSystem>();
    if (!inputSystem->Init()) return false;
    systems[typeid(InputSystem)] = inputSystem.get();

    return true;
}

void SystemRegistry::UnloadEverything()
{
    worldSystem.reset();
    physicsSystem.reset();
    inputSystem.reset();
    timeSystem.reset();
    renderingSystem.reset();
    pathSystem.reset();
    poolSystem.reset();
}