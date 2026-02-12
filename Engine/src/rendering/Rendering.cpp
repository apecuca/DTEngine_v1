#include "Rendering.hpp"

#include <Engine/Window.hpp>

using namespace DTEngine;

void Rendering::InitWindow(int width, int height, std::string name)
{
    window = std::make_unique<DTEngine::Window>(width, height, name);
}

bool Rendering::IsWindowRunning()
{
    if (window == nullptr) return false;
    else if (!window->IsRunning()) return false;

    return true;
}

void Rendering::RenderCycle()
{
    window->Clear();

    window->SwapBuffers();

    window->ReadInputs();
}