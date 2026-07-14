#pragma once

#include <DTEngine/Component.hpp>
#include <DTEngine/GameObject.hpp>
#include <DTEngine/EntityHandle.hpp>
#include <DTEngine/Animator.hpp>
#include <DTEngine/Rigidbody.hpp>
#include <DTEngine/BoxCollider.hpp>

using namespace DTEngine;

class SuperComponent : public Component
{

public:
    virtual ~SuperComponent();
    SuperComponent(GameObject& _gameObject);

    void Awake() override;

    void Start() override;

    void FixedUpdate() override;
    void Update() override;
    void LateUpdate() override;

    void OnCollisionEnter(Collision& col) override;
    void OnCollisionStay(Collision& col) override;
    void OnCollisionExit(Collision& col) override;

    void OnSensorEnter(Collision& col) override;
    void OnSensorStay(Collision& col) override;
    void OnSensorExit(Collision& col) override;

private:
    EntityHandle<Rigidbody> rb;
    EntityHandle<Transform> child;
    
    float moveSpeed = 4.0f;
    float jumpForce = 7.5f;

    float timer = 0.0f;
    bool grounded = false;

};