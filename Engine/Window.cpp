#include "Window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace DTEngine;

Window::~Window()
{
    //
}

Window::Window(int _width, int _height, std::string _name)
{
    if (!glfwInit())
        throw std::string("Failed to initialize GLFW");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    winPtr = glfwCreateWindow(_width, _height, _name.c_str(), NULL, NULL);

    if (!winPtr) {
        glfwTerminate();
        throw std::string("Failed to initialize GLFW");
    }

    glfwMakeContextCurrent(winPtr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::string ("Failed to initialize GLAD");
    }
}

void Window::RenderCycle()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(winPtr);

    glfwPollEvents();
}

bool Window::IsRunning()
{
    return !glfwWindowShouldClose(winPtr);
}