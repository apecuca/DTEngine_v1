#include <DTEngine/BoxCollider.hpp>

#include <DTEngine/GameObject.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"

using namespace DTEngine;

BoxCollider::~BoxCollider()
{
    SystemRegistry::GetSystem<PhysicsSystem>()->RemoveCollider(this);
}

BoxCollider::BoxCollider(GameObject& _gameObject) :
    Component(_gameObject)
{
    size        = Vector2(1.0f, 1.0f);
    sensor      = false;
    bounciness  = 0.05f;
    friction    = 0.3f;

    SystemRegistry::GetSystem<PhysicsSystem>()->AddCollider(this);
}

Bounds BoxCollider::GetBounds() const
{
    Vector2 worldPosition = gameObject.transform->GetPosition();
    Vector2 worldScale = gameObject.transform->GetScale();

    Vector2 center = worldPosition + offset;
    Vector2 extents = size * 0.5f * worldScale;
    Bounds b;
    b.min = center - extents;
    b.max = center + extents;
    return b;
}

