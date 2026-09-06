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

void Camera::OnMarkedForDestruction()
{
    // Clearing main in ~Camera would leave a whole
    // frame between the mark and the end-of-frame free, where Camera::main
    // hands out a camera whose transform handle is already invalid
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

    // Pixels (top-left origin) -> NDC
    Vector3 ndc(
        (point.x / (float)win->width) * 2.0f - 1.0f,
        1.0f - (point.y / (float)win->height) * 2.0f,
        1.0f
    );

    // NDC -> camera space -> world
    Vector3 world = (GetProjectionMatrix() * GetViewMatrix()).Inverse() * ndc;

    return Vector2(world.x, world.y);
}

Vector2 Camera::WorldToScreenPoint(const Vector2& point) const
{
    if (Window::instance == nullptr)
        throw std::runtime_error("No Window instance available");

    Window* win = Window::instance;

    // World -> camera space -> clip space. In an orthographic projection clip
    // space is already NDC, there is no perspective divide (w stays 1)
    Vector3 ndc = (GetProjectionMatrix() * GetViewMatrix()) * Vector3(point, 1.0f);

    // NDC -> pixels, top-left origin (same convention as ScreenToWorldPoint
    // and InputManager::GetMousePosition)
    return Vector2(
        (ndc.x + 1.0f) * 0.5f * (float)win->width,
        (1.0f - ndc.y) * 0.5f * (float)win->height
    );
}

Matrix3 Camera::GetViewMatrix() const
{
    Vector2 camPos = gameObject.transform->GetPosition();
    float camRot = gameObject.transform->GetRotation();

    // Undo the camera rotation, then bring the camera back to the origin.
    // Composed, this rotates the world using camPos as the pivot
    Matrix3 view = Matrix3::Rotate(Matrix3::Identity(), -Radians(camRot));
    view = Matrix3::Translate(view, -camPos);

    return view;
}

Matrix3 Camera::GetProjectionMatrix() const
{
    if (Window::instance == nullptr)
        throw std::runtime_error("No Window instance available");

    Window* win = Window::instance;

    float aspect = (float)win->width / (float)win->height;

    return Matrix3::Ortho(-aspect * fov, aspect * fov, -fov, fov);
}