#include "Engine.hpp"

#include "Window.hpp"

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine()
{
    running = true;
}

void Engine::InitWindow(int width, int height, std::string name)
{
    window = std::make_unique<DTEngine::Window>(width, height, name);
}

void Engine::Run()
{
    while (!ShouldStop()) {
        window->RenderCycle();
    }
}

bool Engine::ShouldStop()
{
    if (running && window->IsRunning())
        return false;
    
    return true;
}