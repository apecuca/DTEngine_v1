#include <World.hpp>

#include <iostream>
#include <algorithm>

#include "GameObject.hpp"

using namespace DTEngine;

World::~World()
{
    //
}

World::World()
{
    //
}

GameObject* World::Instantiate()
{
    std::unique_ptr<GameObject> newObj = std::make_unique<GameObject>();
    GameObject* raw = newObj.get();
    gameObjects.emplace_back(std::move(newObj));

    return raw; 
}

void World::Destroy(const GameObject* obj)
{
    auto it = std::find_if(gameObjects.begin(), gameObjects.end(),
        [obj](const std::unique_ptr<GameObject>& ptr)
        {
            return ptr.get() == obj;
        });

    if (it != gameObjects.end())
        it->get()->MarkForDestruction();
}

void World::ProcessDestroyQueue()
{
    gameObjects.erase(
        std::remove_if(gameObjects.begin(), gameObjects.end(),
            [](const std::unique_ptr<GameObject>& obj)
            {
                return obj->GetMarkedForDestruction();
            }),
        gameObjects.end());
}