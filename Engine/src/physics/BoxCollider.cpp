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

    Vector2 center = Vector2(worldPosition.x + offset.x,
                             worldPosition.y + offset.y);
    Vector2 half = size * 0.5f;
    Bounds b;
    b.min = Vector2(center.x - (half.x * worldScale.x), center.y - (half.y * worldScale.y));
    b.max = Vector2(center.x + (half.x * worldScale.x), center.y + (half.y * worldScale.y));
    return b;
}

