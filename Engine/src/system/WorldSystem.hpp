#ifndef DTENGINE_WORLDSYSTEM_H
#define DTENGINE_WORLDSYSTEM_H

#include "system/InternalSystem.hpp"

#include <memory>
#include <functional>
#include <string>
#include <utility>

namespace DTEngine
{

class World;

struct WorldBlueprint
{
public:
   ~WorldBlueprint() = default;
   WorldBlueprint(const std::string& _name, bool _defaultObjects, std::function<void()> _startFunction) :
      name(_name), defaultObjects(_defaultObjects), startFunction(_startFunction) { }

   const std::string name;
   const bool defaultObjects; // Should instantiate default world objects, like a Camera
   std::function<void()> startFunction;
};

class WorldSystem : public InternalSystem
{
friend class SystemRegistry;
friend class Engine;

public:
    ~WorldSystem();
    WorldSystem();

public:
    // Saves a world to be loaded
    int RegisterWorld(std::string name, std::function<void()> startFunction, bool defaultObjects);
    void LoadWorld(int index);
    void LoadWorld(const std::string& name);

    World* GetActiveWorld();
    bool IsWorldActive();
    
protected:
    bool Init() override;
    void OnEndOfFrame();
    
private:
    void UpdateActiveWorld();
    void FixedUpdateActiveWorld();

    // Applies a pending world load, if any (safe point only)
    void ProcessWorldLoad();

    int GetWorldIndex(std::string name);

private:
    std::unique_ptr<World> activeWorld;

    std::vector<WorldBlueprint> registeredWorlds;

    bool worldLoadPending = false;
    int  pendingWorldIndex = -1;

};

}

#endif