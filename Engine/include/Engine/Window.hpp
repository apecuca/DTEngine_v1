#ifndef INCLUDED_WINDOW_H
#define INCLUDED_WINDOW_H
#pragma once

#include <iostream>

class GLFWwindow;

namespace DTEngine {
class Window
{
public:
    ~Window();
    Window(int _width, int _height, std::string _name);
    
    void Clear();
    void SwapBuffers();
    void ReadInputs();

    bool IsRunning();

private:
    static void callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight);

private:
    GLFWwindow* winPtr;

    int width, height;

    static DTEngine::Window* instance;
};
}

#endif