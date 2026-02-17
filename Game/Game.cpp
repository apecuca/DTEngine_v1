#include "Game.hpp"

#include "Engine.hpp"
#include <Engine/World.hpp>
#include <memory>

using namespace DTEngine;

Game::Game(DTEngine::Engine& _eng) :
engine(_eng)
{
    std::unique_ptr<World> _world = std::make_unique<World>();

    GameObject* newobj = _world->Instantiate();
    _world->Destroy(newobj);

    engine.InitWindow(800, 600, "Omg hi bestie");
    engine.LoadWorld(_world);

}