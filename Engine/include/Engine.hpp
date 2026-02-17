#ifndef INCLUDED_ENGINE_H
#define INCLUDED_ENGINE_H
#pragma once

#include <iostream>
#include <memory>

namespace DTEngine {

class Window;
class Rendering;
class World;

class Engine
{
public:
    Engine();
    ~Engine();

public:
    // Initialized the main window
    void InitWindow(int width, int height, std::string name);

    void LoadWorld(std::unique_ptr<World>& world);

    // Called once to start, runs the engine's main loop
    void Run();

private:
    // Returns if the engine should stop running
    bool ShouldStop();

private:
    std::unique_ptr<Rendering> rendering;
    std::unique_ptr<World> activeWorld;

    bool running;
};
}

#endif