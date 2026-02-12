#include "Window.hpp"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

DTEngine::Window* DTEngine::Window::instance;

using namespace DTEngine;

Window::~Window()
{
    //
}

Window::Window(int _width, int _height, std::string _name)
:
width(_width), height(_height)
{
    if (instance != nullptr)
        throw std::string("Duplicated window instance");
    
    instance = this;

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

    // Set viewport size
	glViewport(0, 0, width, height);

	// Enable vsync
	glfwSwapInterval(1); 

	// Blend function (alpha channel support)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Set callbacks
	glfwSetFramebufferSizeCallback(winPtr, callback_framebufferSize);
}

void Window::Clear()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(winPtr);
}

void Window::ReadInputs()
{
    glfwPollEvents();
}

bool Window::IsRunning()
{
    return !glfwWindowShouldClose(winPtr);
}

void Window::callback_framebufferSize(GLFWwindow* window, int newWidth, int newHeight)
{
	instance->width = newWidth;
	instance->height = newHeight;

	glViewport(0, 0, instance->width, instance->height);
}