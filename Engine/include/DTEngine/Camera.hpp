#ifndef DTENGINE_CAMERA_H
#define DTENGINE_CAMERA_H
#pragma once

#include <DTEngine/Component.hpp>

namespace DTEngine
{

class Camera : public Component
{
public:
    ~Camera();
    Camera(GameObject& _gameObject);

public:
    Vector2 ScreenToWorldPoint(const Vector2& point) const;

private:
    constexpr static float defaultFov = 5.0f;

public:
    float fov;

    static Camera* main;

};

}

#endif