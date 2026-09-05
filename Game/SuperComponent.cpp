#include "SuperComponent.hpp"

#include <DTEngine/TimeManager.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/WorldManager.hpp>
#include <DTEngine/SpriteRenderer.hpp>
#include <DTEngine/InputManager.hpp>
#include <DTEngine/RenderingManager.hpp>
#include <DTEngine/PhysicsManager.hpp>
#include <DTEngine/Camera.hpp>

#include <DTEngine/Utils.hpp>

#include <iostream>
#include <string>

using namespace DTEngine;

SuperComponent::~SuperComponent()
{
    //
}

SuperComponent::SuperComponent(GameObject& _gameObject) :
    Component(_gameObject)
{
    //
}

void SuperComponent::Awake()
{
    rb = gameObject.GetComponent<Rigidbody>();
}

void SuperComponent::Start()
{
    if (gameObject.transform->ChildCount() > 0) {
        child = gameObject.transform->ChildAt(0);
        cameraFollow = false;
    }
}

void SuperComponent::FixedUpdate()
{
    //
}

void SuperComponent::Update()
{
    x = 0.0f;

    std::vector<RaycastHit> hit;
    Vector2 feetPosition = gameObject.transform->GetPosition();
    feetPosition.y -= 0.55f;
    grounded = PhysicsManager::OverlapBox(feetPosition, Vector2(1.0f, 0.1f),
                                          PhysicsManager::GetLayerMask({"Ground"}), hit);

    if (InputManager::GetKey(DTK_LCTRL)) {
        gameObject.transform->SetPosition(Camera::main->ScreenToWorldPoint(InputManager::GetMousePosition()));
        rb->linearVelocity = Vector2::zero();

        if (InputManager::GetKey(DTK_R))
            gameObject.transform->localRotation += 180.0f * TimeManager::GetDeltaTime();
    }
    else {
        if (InputManager::GetKey(DTK_RIGHT))
            x += 1.0f;
        if (InputManager::GetKey(DTK_LEFT))
            x -= 1.0f;

        if (InputManager::GetKey(DTK_SPACE) && grounded)
            rb->linearVelocity.y = jumpForce;
    }

    if (InputManager::GetKeyDown(DTK_C) && child) {
        if (gameObject.transform->ChildCount() == 0)
            child->SetParent(gameObject.transform);
        else
            child->SetParent(nullptr);
    }

    rb->linearVelocity.x = x * moveSpeed;

    if (InputManager::GetKeyDown(DTK_ALPHA1))
        WorldManager::LoadWorld("First");

    if (InputManager::GetKeyDown(DTK_ALPHA2))
        WorldManager::LoadWorld(1);
}

void SuperComponent::LateUpdate()
{
    auto pos = gameObject.transform->GetPosition();
    auto rot = Camera::main->gameObject.transform->GetRotation();
    if (cameraFollow)
        Camera::main->gameObject.transform->SetPosition(pos);
    if (InputManager::GetKey(DTK_E))
        Camera::main->gameObject.transform->SetRotation(rot + (180.0f * TimeManager::GetDeltaTime()));
    if (InputManager::GetKey(DTK_Q))
        Camera::main->gameObject.transform->SetRotation(rot - (180.0f * TimeManager::GetDeltaTime()));
}

void SuperComponent::OnCollisionEnter(Collision& col)
{
    //
}

void SuperComponent::OnCollisionStay(Collision& col)
{
    //
}

void SuperComponent::OnCollisionExit(Collision& col)
{
    //
}

void SuperComponent::OnSensorEnter(Collision& col)
{
    //
}

void SuperComponent::OnSensorStay(Collision& col)
{
    //
}

void SuperComponent::OnSensorExit(Collision& col)
{
    //
}