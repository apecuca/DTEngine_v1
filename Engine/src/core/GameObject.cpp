#include <GameObject.hpp>

#include <DTEngine/World.hpp>
#include <DTEngine/Component.hpp>
#include <DTEngine/BoxCollider.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"
#include "system/PoolSystem.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>

using namespace DTEngine;

namespace
{

// Division that degenerates to 0 instead of exploding on a (near-)zero
// parent scale
float SafeDiv(float numerator, float denominator)
{
    if (std::abs(denominator) < 1e-6f)
        return 0.0f;

    return numerator / denominator;
}

Vector2 SafeDiv(const Vector2& numerator, const Vector2& denominator)
{
    return Vector2(SafeDiv(numerator.x, denominator.x),
                   SafeDiv(numerator.y, denominator.y));
}

// Rotates a vector counter-clockwise around the origin
Vector2 RotateVector(const Vector2& v, float degrees)
{
    float radians = degrees * (3.14159265358979f / 180.0f);
    float c = std::cos(radians);
    float s = std::sin(radians);
    return Vector2(v.x * c - v.y * s, v.x * s + v.y * c);
}

}

GameObject::~GameObject()
{
    // Components live in the global pool; release them with their owner
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    if (pool != nullptr) {
        for (auto& ref : componentRefs)
            if (ref.IsAlive())
                pool->Release(ref.ptr);
    }
}

GameObject::GameObject() :
    Entity(),
    position(0.0f, 0.0f),
    scale(1.0f, 1.0f),
    clickable(true)
{
    SetLayer("Default");
}

void GameObject::MarkForDestruction()
{
    if (markedForDestruction)
        return;

    markedForDestruction = true;

    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->markedForDestruction = true;
    }

    // Destruction cascades down the hierarchy
    for (auto& child : children) {
        GameObject* childObject = child.Get();
        if (childObject != nullptr)
            childObject->MarkForDestruction();
    }
}

void GameObject::ProcessComponentDestructionQueue()
{
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    if (pool == nullptr)
        return;

    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;

        if (static_cast<Component*>(ref.ptr)->markedForDestruction)
            pool->Release(ref.ptr);
    }

    std::erase_if(componentRefs, [](const EntitySlotRef& ref) { return !ref.IsAlive(); });
}

bool GameObject::GetMarkedForDestruction() const
{
    return markedForDestruction;
}

EntitySlotRef GameObject::AddComponentImpl(std::unique_ptr<Component> component)
{
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();

    EntitySlotRef ref = pool->Acquire(std::move(component));
    componentRefs.emplace_back(ref);

    return ref;
}

EntitySlotRef GameObject::FindComponentImpl(const std::type_info& type) const
{
    EntitySlotRef found;

    for (const auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;

        if (typeid(*ref.ptr) == type)
            found = ref;
    }

    return found;
}

EntityHandle<GameObject> GameObject::GetHandle() const
{
    return EntityHandle<GameObject>(selfRef);
}

void GameObject::SetParent(const EntityHandle<GameObject>& newParent)
{
    GameObject* target = newParent.Get();

    // Reject self-parenting and hierarchy cycles before mutating anything;
    // with cascading destruction a cycle would recurse forever
    for (GameObject* ancestor = target; ancestor != nullptr; ancestor = ancestor->parent.Get()) {
        if (ancestor == this) {
            std::cerr << "[GameObject] SetParent: would create a hierarchy cycle\n";
            return;
        }
    }

    if (parent == newParent)
        return;

    // Preserve the world transform across the reparent: the local values
    // are recomputed against the new parent so the object doesn't move
    Vector2 worldPosition = GetWorldPosition();
    Vector2 worldScale = GetWorldScale();
    Vector3 worldRotation = GetWorldRotation();

    GameObject* current = parent.Get();
    if (current != nullptr)
        current->RemoveChild(GetHandle());

    if (target == nullptr) {
        parent = EntityHandle<GameObject>{};
        position = worldPosition;
        scale = worldScale;
        rotation = worldRotation;
        return;
    }

    parent = newParent;
    target->AddChild(GetHandle());

    Vector3 parentRotation = target->GetWorldRotation();
    rotation = Vector3(worldRotation.x - parentRotation.x,
                       worldRotation.y - parentRotation.y,
                       worldRotation.z - parentRotation.z);
    scale = SafeDiv(worldScale, target->GetWorldScale());
    SetWorldPosition(worldPosition);
}

EntityHandle<GameObject> GameObject::GetParent() const
{
    return parent;
}

void GameObject::AddChild(const EntityHandle<GameObject>& obj)
{
    int position;
    if (HasChild(obj, position))
        return;

    children.emplace_back(obj);
}

void GameObject::RemoveChild(const EntityHandle<GameObject>& obj)
{
    int position;
    if (!HasChild(obj, position))
        return;

    children.erase(children.begin() + position);
}

void GameObject::PruneChildren()
{
    std::erase_if(children, [](const EntityHandle<GameObject>& child) {
        return !child.IsValid();
    });
}

int GameObject::ChildCount()
{
    PruneChildren();

    return static_cast<int>(children.size());
}

EntityHandle<GameObject> GameObject::ChildAt(int position)
{
    PruneChildren();

    if (position < 0 || position >= (int)children.size())
        throw std::runtime_error("Child position " + std::to_string(position) + " out of bounds");

    return children.at(position);
}

bool GameObject::HasChild(const EntityHandle<GameObject>& obj, int& outPosition)
{
    PruneChildren();

    outPosition = -1;
    if (obj == nullptr)
        return false;

    for (int i = 0; i < children.size(); i++) {
        if (children[i] == obj) {
            outPosition = i;
            return true;
        }
    }

    return false;
}

void GameObject::SetLayer(const std::string& layerName)
{
    // PhysicsSystem may not exist yet during engine bootstrap; skip validation then
    PhysicsSystem* physics = SystemRegistry::GetSystem<PhysicsSystem>();
    if (physics != nullptr && !physics->HasLayer(layerName)) {
        std::cerr << "[GameObject] SetLayer: layer '" << layerName << "' does not exist\n";
        return;
    }

    layer = layerName;
}

std::string GameObject::GetLayer() const
{
    return layer;
}

Vector2 GameObject::GetWorldScale() const
{
    GameObject* parentObject = parent.Get();
    if (parentObject == nullptr)
        return scale;

    return parentObject->GetWorldScale() * scale;
}

Vector3 GameObject::GetWorldRotation() const
{
    GameObject* parentObject = parent.Get();
    if (parentObject == nullptr)
        return rotation;

    Vector3 parentRotation = parentObject->GetWorldRotation();
    return Vector3(parentRotation.x + rotation.x,
                   parentRotation.y + rotation.y,
                   parentRotation.z + rotation.z);
}

Vector2 GameObject::GetWorldPosition() const
{
    GameObject* parentObject = parent.Get();
    if (parentObject == nullptr)
        return position;

    // The local offset scales with the parent and orbits its pivot
    Vector2 offset = parentObject->GetWorldScale() * position;
    offset = RotateVector(offset, parentObject->GetWorldRotation().z);

    return parentObject->GetWorldPosition() + offset;
}

void GameObject::SetWorldPosition(const Vector2& worldPosition)
{
    GameObject* parentObject = parent.Get();
    if (parentObject == nullptr) {
        position = worldPosition;
        return;
    }

    Vector2 parentPosition = parentObject->GetWorldPosition();
    Vector2 delta(worldPosition.x - parentPosition.x, worldPosition.y - parentPosition.y);
    delta = RotateVector(delta, -parentObject->GetWorldRotation().z);
    position = SafeDiv(delta, parentObject->GetWorldScale());
}

void GameObject::InternalAwake()
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->Awake();
    }
}

void GameObject::InternalStart()
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->Start();
    }
}
void GameObject::InternalFixedUpdate()
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->FixedUpdate();
    }
}

void GameObject::InternalUpdate()
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->Update();
    }
}

void GameObject::InternalLateUpdate()
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->LateUpdate();
    }
}

void GameObject::ReceiveCollisionMessage(Collision& collision)
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;

        Component* component = static_cast<Component*>(ref.ptr);
        switch (collision.type) {
            case CollisionType::ENTER:
                component->OnCollisionEnter(collision);
                break;

            case CollisionType::STAY:
                component->OnCollisionStay(collision);
                break;

            case CollisionType::EXIT:
                component->OnCollisionExit(collision);
                break;
        }
    }
}

void GameObject::ReceiveSensorMessage(Collision& collision)
{
    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;

        Component* component = static_cast<Component*>(ref.ptr);
        switch (collision.type) {
            case CollisionType::ENTER:
                component->OnSensorEnter(collision);
                break;

            case CollisionType::STAY:
                component->OnSensorStay(collision);
                break;

            case CollisionType::EXIT:
                component->OnSensorExit(collision);
                break;
        }
    }
}