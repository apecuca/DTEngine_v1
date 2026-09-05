#include "Camera.hpp"

#include <DTEngine/GameObject.hpp>
#include <DTEngine/Window.hpp>

#include <stdexcept>

using namespace DTEngine;

Camera* Camera::main = nullptr;

Camera::~Camera()
{
    if (main == this)
        main = nullptr;
}

Camera::Camera(GameObject& _gameObject) :
    Component(_gameObject),
    fov(defaultFov)
{
    if (main == nullptr)
        main = this;
}

Vector2 Camera::ScreenToWorldPoint(const Vector2& point) const
{
    if (Window::instance == nullptr)
        throw std::runtime_error("No Window instance available");

    Window* win = Window::instance;

    float aspect = (float)win->width / (float)win->height;
    float ndcX = (point.x / (float)win->width) * 2.0f - 1.0f;
    float ndcY = 1.0f - (point.y / (float)win->height) * 2.0f;
    return Vector2(ndcX * aspect * fov, ndcY * fov);
}