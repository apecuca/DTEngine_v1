#include "Game.hpp"

#include "Engine/Engine.hpp"

using namespace DTEngine;

Game::Game(DTEngine::Engine& _eng) :
engine(_eng)
{
    engine.InitWindow(800, 600, "Omg hi bestie");
}