#include "CameraFollow.hpp"

#include <DTEngine/Camera.hpp>
#include <DTEngine/InputManager.hpp>
#include <DTEngine/TimeManager.hpp>

#include <iostream>

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

void CameraFollow::Update()
{
    auto rot = gameObject.transform->GetRotation();

    if (InputManager::GetKey(DTK_E))
        gameObject.transform->SetRotation(rot + (180.0f * TimeManager::GetDeltaTime()));
    if (InputManager::GetKey(DTK_Q))
        gameObject.transform->SetRotation(rot - (180.0f * TimeManager::GetDeltaTime()));
}

void CameraFollow::FixedUpdate()
{
    auto cPos = gameObject.transform->GetPosition();
    auto tPos = Vector2();

    if (followTarget)
        tPos = followTarget->GetPosition();

    auto newPos = DTMath::Lerp(cPos, tPos, 10.0f * TimeManager::GetFixedTimeStep());
    gameObject.transform->SetPosition(newPos);
}

void CameraFollow::SetTarget(EntityHandle<Transform> target)
{
    followTarget = target;
}