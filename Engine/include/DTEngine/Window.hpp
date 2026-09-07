#ifndef DTENGINE_WINDOW_H
#define DTENGINE_WINDOW_H
#pragma once

#include <iostream>

class GLFWwindow;

namespace DTEngine {

struct Vector2;

class Window
{
friend class RenderingSystem;
friend class Engine;
friend class TimeSystem;
friend class InputSystem;
friend class Camera;

public:
    ~Window();
    Window(int _width, int _height, std::string _name);

public:
    Vector2 GetSize() const;

    void SetSolidState(bool state, bool overrideInternalLogic);

    static inline Window* GetInstance() { return instance; }

private:
    void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 0.0f);
    void SwapBuffers();
    void ReadInputs();
    void UpdateSolidState();

    bool IsRunning() const;

    void ConfigWindow();

    static void callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight);

private:
    GLFWwindow* winPtr;

    bool solid;
    bool overridingState;
    int width, height;

    static DTEngine::Window* instance;
};
}

#endif