#include "Engine.hpp"

#include "Window.hpp"
#include "Internal/Rendering.hpp"

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine()
{
    // Internal stuff
    rendering = std::make_unique<DTEngine::Rendering>();

    running = true;
}

void Engine::InitWindow(int width, int height, std::string name)
{
    window = std::make_unique<DTEngine::Window>(width, height, name);
}

void Engine::Run()
{
    if (window == nullptr)
        throw std::string("Window was not initialized.");

    while (!ShouldStop()) {
        window->RenderCycle();
    }
}

bool Engine::ShouldStop()
{
    if (window == nullptr)
        return true;

    if (running && window->IsRunning())
        return false;
    
    return true;
}