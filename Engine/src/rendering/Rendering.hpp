#ifndef INCLUDED_RENDERING_H
#define INCLUDED_RENDERING_H

#include <iostream>
#include <memory>

namespace DTEngine {

class Window;

class Rendering
{
public:
    ~Rendering() = default;
    Rendering() = default;
    
    // Initialized the main window
    void InitWindow(int width, int height, std::string name);
    
    // Returns if the main window is still running
    bool IsWindowRunning();

    void RenderCycle();

private:
    std::unique_ptr<DTEngine::Window> window;
};
}

#endif