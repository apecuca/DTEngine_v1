#include <DTEngine/Engine.hpp>

#include <DTEngine/Window.hpp>
#include <DTEngine/World.hpp>

#include "system/WorldSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/SystemRegistry.hpp"
#include "system/PathSystem.hpp"
#include "system/TimeSystem.hpp"
#include "system/InputSystem.hpp"
#include "system/PhysicsSystem.hpp"

#include "GLFW/glfw3.h"
#include <stdexcept>

//std::unique_ptr<DTEngine::World> DTEngine::Engine::activeWorld;

using namespace DTEngine;

Engine::~Engine()
{
    //
}

Engine::Engine(const std::string& assetsPath, const std::string& resourcesPath)
{
    // Internal stuff
    systemRegistry = std::make_unique<SystemRegistry>();
    if (!systemRegistry->InitWorks(assetsPath, resourcesPath))
        throw std::runtime_error("Failed to initialize internal systems");

    running = true;
}

void Engine::Run()
{
    // Main systems
    WorldSystem* sys_world = systemRegistry->GetSystem<WorldSystem>();
    RenderingSystem* sys_rendering = systemRegistry->GetSystem<RenderingSystem>();
    TimeSystem* sys_time = systemRegistry->GetSystem<TimeSystem>();
    InputSystem* sys_input = systemRegistry->GetSystem<InputSystem>();
    PhysicsSystem* sys_physics = systemRegistry->GetSystem<PhysicsSystem>();

    // Apply any world load requested before the loop started (e.g. from Game's
    // constructor). LoadWorld only marks the request as pending now.
    sys_world->ProcessWorldLoad();

    if (!sys_rendering->IsWindowRunning())
        throw std::runtime_error("Window was not initialized.");

    if (!sys_world->IsWorldActive())
        throw std::runtime_error("No world loaded.");

    while (!ShouldStop()) {
        
        //
        // This is the main loop of the engine
        //
        
        // Update internal pre-render stuff
        Window::instance->ReadInputs();
        sys_input->ReadInputs();
        sys_time->UpdateTimeVariables();

        // Each physics step gets its own FixedUpdate, so forces applied there
        // are not swallowed by the first step of a catch-up frame
        int fixedCatchUpTimes = sys_time->ConsumeFixedSteps();

        for (int i = 0; i < fixedCatchUpTimes; i++) {
            sys_world->FixedUpdateActiveWorld();

            // Update active physics bodies
            sys_physics->UpdatePhysics();
        }

        // Update behaviours
        sys_world->UpdateActiveWorld();

        // Render call
        sys_rendering->RenderCycle();

        // Finish frame
        sys_world->OnEndOfFrame();
        sys_input->OnEndOfFrame();
    }

    systemRegistry->UnloadEverything();
}

bool Engine::ShouldStop()
{
    if (!systemRegistry->IsFullyWorking())
        return true;

    if (running && systemRegistry->GetSystem<RenderingSystem>()->IsWindowRunning())
        return false;
    
    return true;
}