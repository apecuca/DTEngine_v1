#include "Window.hpp"

#include <DTEngine/Utils.hpp>
#include "system/SystemRegistry.hpp"
#include "system/RenderingSystem.hpp"
#include "system/InputSystem.hpp"

#include "glad/glad.h"
#include <stdexcept>
#include "GLFW/glfw3.h"

DTEngine::Window* DTEngine::Window::instance;

using namespace DTEngine;

Window::~Window()
{
    instance = nullptr;
}

Window::Window(int _width, int _height, std::string _name)
:
width(_width), height(_height), fov(defaultFov), overridingState(false)
{
    if (instance != nullptr)
        throw std::runtime_error("Duplicated window instance");
    
    instance = this;

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);

    // Same size as the screen results in black background
    width = mode->width + 1;
    height = mode->height + 1;

    winPtr = glfwCreateWindow(width, height, _name.c_str(), NULL, NULL);

    if (!winPtr) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize Window");
    }

    int xpos, ypos;
    glfwGetMonitorPos(monitor, &xpos, &ypos);
    glfwSetWindowPos(winPtr, xpos, ypos);
}

void Window::ConfigWindow()
{
    // Set viewport size
	glViewport(0, 0, width, height);

    // Set callbacks
	glfwSetFramebufferSizeCallback(winPtr, callback_framebufferSize);
}

void Window::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(winPtr);
}

void Window::ReadInputs()
{
    glfwPollEvents();

    UpdateSolidState();
}

void Window::UpdateSolidState()
{
    if (overridingState)
        return;

    Vector2 mousePos = SystemRegistry::GetSystem<InputSystem>()->GetMousePosition();
    bool newSolid = SystemRegistry::GetSystem<RenderingSystem>()->IsPositionSolid(mousePos.x, mousePos.y, GetSize());
    if (newSolid != solid)
        SetSolidState(newSolid, false);
}

void Window::SetSolidState(bool state, bool overrideInternalLogic)
{
    solid = state;
    overridingState = overrideInternalLogic;
    glfwSetWindowAttrib(winPtr, GLFW_MOUSE_PASSTHROUGH, !solid);
}

bool Window::IsRunning() const
{
    return !glfwWindowShouldClose(winPtr);
}

void Window::callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	instance->width = newWidth + 1;
	instance->height = newHeight + 1;

	glViewport(0, 0, instance->width, instance->height);
}

Vector2 Window::GetSize() const
{
    return Vector2(width, height);
}

Vector2 Window::ScreenToWorldPoint(const Vector2& point) const
{
    float aspect = (float)width / (float)height;
    float ndcX   = (point.x / (float)width)  * 2.0f - 1.0f;
    float ndcY   = 1.0f - (point.y / (float)height) * 2.0f;
    return Vector2(ndcX * aspect * fov, ndcY * fov);
}