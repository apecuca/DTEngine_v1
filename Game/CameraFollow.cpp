#include "CameraFollow.hpp"

#include <DTEngine/Camera.hpp>
#include <DTEngine/InputManager.hpp>
#include <DTEngine/TimeManager.hpp>

using namespace DTEngine;

CameraFollow::~CameraFollow()
{
    //
}

CameraFollow::CameraFollow(GameObject& _gameObject) :
    Component(_gameObject)
{
    //
}

void CameraFollow::LateUpdate()
{
    auto rot = gameObject.transform->GetRotation();

    if (followTarget)
        gameObject.transform->SetPosition(followTarget->GetPosition());

    if (InputManager::GetKey(DTK_E))
        gameObject.transform->SetRotation(rot + (180.0f * TimeManager::GetDeltaTime()));
    if (InputManager::GetKey(DTK_Q))
        gameObject.transform->SetRotation(rot - (180.0f * TimeManager::GetDeltaTime()));
}

void CameraFollow::SetTarget(EntityHandle<Transform> target)
{
    followTarget = target;
}