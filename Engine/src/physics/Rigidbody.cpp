#include <DTEngine/Rigidbody.hpp>

#include <DTEngine/Utils.hpp>
#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"
#include "system/TimeSystem.hpp"

#include <algorithm>

using namespace DTEngine;

Rigidbody::~Rigidbody()
{
	SystemRegistry::GetSystem<PhysicsSystem>()->RemovePhysicsSource(this);
}

Rigidbody::Rigidbody(GameObject& _gameObject) :
	Component(_gameObject)
{
    gravityScale    = 1.0f;
    mass            = 1.0f;
    linearDrag      = 0.0f;
    //angularDrag     = 0.05f;
    //angularVelocity = 0.0f;
    isKinematic     = false;

	SystemRegistry::GetSystem<PhysicsSystem>()->AddPhysicsSource(this);
}

void Rigidbody::UpdatePhysics()
{
    if (isKinematic) return;

    auto sys_physics = SystemRegistry::GetSystem<PhysicsSystem>();
    auto sys_time = SystemRegistry::GetSystem<TimeSystem>();
    float dt = (float)sys_time->GetFixedTimeStep();

    // Linear
    linearVelocity += (sys_physics->GetGravity() * gravityScale + acceleration) * dt;
    linearVelocity = linearVelocity * std::max(0.0f, 1.0f - linearDrag * dt);
    gameObject.SetWorldPosition(gameObject.GetWorldPosition() + linearVelocity * dt);

    // Angular (for a future update on collision)
    //gameObject.rotation.z += angularVelocity * dt;
    //angularVelocity *= std::max(0.0f, 1.0f - angularDrag * dt);

    acceleration = Vector2(0.0f, 0.0f);
}

void Rigidbody::AddForce(Vector2 force)
{
    if (isKinematic) return;
    acceleration += force * (1.0f / mass);
}