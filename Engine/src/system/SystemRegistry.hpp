#ifndef DTENGINE_INTERNALWORKS_H
#define DTENGINE_INTERNALWORKS_H

#include <memory>
#include <unordered_map>
#include <typeindex>

namespace DTEngine
{

class PoolSystem;
class RenderingSystem;
class WorldSystem;
class PathSystem;
class TimeSystem;
class InputSystem;
class InternalSystem;
class PhysicsSystem;

class SystemRegistry
{
friend class Engine;

public:
    ~SystemRegistry();
    SystemRegistry();

public:
    template <typename T>
    static T* GetSystem()
    {
        if (instance == nullptr)
            return nullptr;

        auto it = instance->systems.find(typeid(T));
        if (it != instance->systems.end())
            return static_cast<T*>(it->second);
        return nullptr;
    }

private:
    bool InitWorks(const std::string& assetsPath, const std::string& resourcesPath);
    bool IsFullyWorking() const;
    void UnloadEverything();

private:
    static SystemRegistry* instance;

    std::unordered_map<std::type_index, InternalSystem*> systems;

    std::unique_ptr<PoolSystem> poolSystem;
    std::unique_ptr<RenderingSystem> renderingSystem;
    std::unique_ptr<WorldSystem> worldSystem;
    std::unique_ptr<PathSystem> pathSystem;
    std::unique_ptr<TimeSystem> timeSystem;
    std::unique_ptr<InputSystem> inputSystem;
    std::unique_ptr<PhysicsSystem> physicsSystem;
};

}

#endif