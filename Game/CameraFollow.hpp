#pragma once

#include <DTEngine/Component.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>

using namespace DTEngine;

class CameraFollow : public Component
{

public:
    virtual ~CameraFollow();
    CameraFollow(GameObject& _gameObject);

    void LateUpdate() override;

    void SetTarget(EntityHandle<Transform> target);

private:
    EntityHandle<Transform> followTarget;

};