#ifndef DTENGINE_CAMERA_H
#define DTENGINE_CAMERA_H
#pragma once

#include <DTEngine/Component.hpp>
#include <DTEngine/Utils.hpp>

namespace DTEngine
{

class Camera : public Component
{
public:
    ~Camera();
    Camera(GameObject& _gameObject);

public:
    Vector2 ScreenToWorldPoint(const Vector2& point) const;
    Vector2 WorldToScreenPoint(const Vector2& point) const;

    // World space -> camera space (the inverse of the camera's world transform)
    Matrix3 GetViewMatrix() const;
    // Camera space -> clip space (orthographic, derived from fov and the window aspect)
    Matrix3 GetProjectionMatrix() const;

private:
    // Removed the main camera pointer as soon as the camera is destroyed, so no
    // one reads a dead camera during the rest of the frame. ~Camera repeats it
    // for the paths that free without marking (world swap, shutdown)
    void OnMarkedForDestruction() override;

private:
    constexpr static float defaultFov = 5.0f;

public:
    float fov;

    static Camera* main;

};

}

#endif