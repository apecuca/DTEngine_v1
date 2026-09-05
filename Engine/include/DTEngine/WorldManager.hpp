#ifndef DTENGINE_WORLDMANAGER_H
#define DTENGINE_WORLDMANAGER_H

//
// This class serves as a communication interface 
// with the internal world system
// 

#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <functional>
#include <string>

namespace DTEngine
{

class World;

class WorldManager final
{
public:
    static int RegisterWorld(const std::string& name, std::function<void()> startFunction, bool defaultObjects = true);
    static void LoadWorld(int index);
    static void LoadWorld(const std::string& name);
    static EntityHandle<GameObject> Instantiate(const std::string& name = "GameObject");
    static void Destroy(const EntityHandle<GameObject>& object);

private:
    ~WorldManager() = default;
    WorldManager() = default;

};

}

#endif