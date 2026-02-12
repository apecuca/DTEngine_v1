#include "Engine.hpp"

#include "Engine/Window.hpp"
#include "GLFW/glfw3.h"
#include "rendering/Rendering.hpp"

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
    rendering->InitWindow(width, height, name);
    //window = std::make_unique<DTEngine::Window>(width, height, name);
}

void Engine::Run()
{
    if (!rendering->IsWindowRunning())
        throw std::string("Window was not initialized.");

    while (!ShouldStop()) {
        rendering->RenderCycle();
    }
}

bool Engine::ShouldStop()
{
    if (rendering == nullptr)
        return true;

    if (running && rendering->IsWindowRunning())
        return false;
    
    return true;
}