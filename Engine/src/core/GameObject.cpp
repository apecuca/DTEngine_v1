#include <GameObject.hpp>

#include <DTEngine/World.hpp>
#include <DTEngine/Component.hpp>
#include <DTEngine/BoxCollider.hpp>
#include "system/SystemRegistry.hpp"
#include "system/PhysicsSystem.hpp"
#include "system/PoolSystem.hpp"

#include <algorithm>
#include <iostream>
#include <string>

using namespace DTEngine;

GameObject::~GameObject()
{
    // Components live in the global pool; release them with their owner
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    if (pool != nullptr) {
        for (auto& ref : componentRefs)
            if (ref.IsAlive())
                pool->Release(ref.ptr);

        if (transformRef.IsAlive())
            pool->Release(transformRef.ptr);
    }
}

GameObject::GameObject() :
    Entity(),
    clickable(true)
{
    SetLayer("Default");

    // The transform lives outside the component list: it doesn't take part
    // in GetComponent/lifecycle calls and is released with the object itself
    PoolSystem* pool = SystemRegistry::GetSystem<PoolSystem>();
    transformRef = pool->Acquire(std::make_unique<Transform>(*this));
    transform = EntityHandle<Transform>(transformRef);
}

void GameObject::MarkForDestruction()
{
    if (markedForDestruction)
        return;

    markedForDestruction = true;

    // Destruction cascades down the hierarchy. This must happen before the
    // components are marked: marking them invalidates the transform handle
    Transform* ownTransform = transform.Get();
    if (ownTransform != nullptr) {
        // Copy: marking a child invalidates its handle inside the original vector
        auto childrenCopy = ownTransform->children;
        for (auto& child : childrenCopy) {
            Transform* childTransform = child.Get();
            if (childTransform != nullptr)
                childTransform->gameObject.MarkForDestruction();
        }
    }

    // Marked so handles to the transform invalidate along with the object
    if (transformRef.IsAlive())
        static_cast<Component*>(transformRef.ptr)->markedForDestruction = true;

    for (auto& ref : componentRefs) {
        if (!ref.IsAlive()) continue;
        static_cast<Component*>(ref.ptr)->markedForDestruction = true;
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