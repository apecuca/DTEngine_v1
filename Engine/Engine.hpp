#ifndef INCLUDED_ENGINE_H
#define INCLUDED_ENGINE_H
#pragma once

#include <iostream>
#include <memory>

namespace DTEngine {

class Window;
class Rendering;

class Engine
{
public:
    Engine();
    ~Engine();

public:
    // Initialized the main window
    void InitWindow(int width, int height, std::string name);

    // Called once to start, runs the engine's main loop
    void Run();

private:
    // Returns if the engine should stop running
    bool ShouldStop();

private:
    std::unique_ptr<DTEngine::Window> window;
    std::unique_ptr<DTEngine::Rendering> rendering;

    bool running;
};
}

#endif