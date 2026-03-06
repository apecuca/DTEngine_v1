#include "Engine.hpp"

#include "Engine/Window.hpp"
#include "GLFW/glfw3.h"
#include "rendering/Rendering.hpp"
#include "World.hpp"
#include "InternalWorksManager.hpp"

//std::unique_ptr<DTEngine::World> DTEngine::Engine::activeWorld;

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine()
{
    // Internal stuff
    internalWorks = std::make_unique<InternalWorksManager>();
    if (!internalWorks->InitWorks())
        throw std::string("Failed to initialize internal works");

    running = true;
}

void Engine::InitWindow(int width, int height, std::string name)
{
    internalWorks->GetRendering()->InitWindow(width, height, name);
}

void Engine::Run()
{
    if (!internalWorks->GetRendering()->IsWindowRunning())
        throw std::string("Window was not initialized.");

    while (!ShouldStop()) {
        // Update internal variables here

        if (activeWorld == nullptr)
            continue;

        // Update behaviours
        activeWorld->WorldUpdate();

        // Render call
        internalWorks->GetRendering()->RenderCycle();

        // Finish frame
        activeWorld->ProcessDestroyQueue();
    }
}

bool Engine::ShouldStop()
{
    if (!internalWorks->IsFullyWorking())
        return true;

    if (running && internalWorks->GetRendering()->IsWindowRunning())
        return false;
    
    return true;
}

World* Engine::LoadWorld(std::unique_ptr<World>& world)
{
    activeWorld.reset(world.release());
    activeWorld->WorldStart();
    return activeWorld.get();
}

/*
World* Engine::GetActiveWorld()
{
    if (activeWorld != nullptr)
        return activeWorld.get();

    return nullptr;
}
*/