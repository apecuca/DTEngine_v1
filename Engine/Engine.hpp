#ifndef INCLUDED_ENGINE_H
#define INCLUDED_ENGINE_H
#pragma once

#include <iostream>

namespace DTEngine {
class Engine
{
public:
    Engine();
    ~Engine() = default;

public:
    // Initialized the main window
    void InitWindow(int width, int height, std::string name);

    // Called once to start, runs the engine's main loop
    void Run();
};
}

#endif