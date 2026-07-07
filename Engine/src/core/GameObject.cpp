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

    GameObject* current = parent.Get();
    if (current != nullptr)
        current->RemoveChild(GetHandle());

    if (target == nullptr) {
        parent = EntityHandle<GameObject>{};
        return;
    }

    parent = newParent;
    target->AddChild(GetHandle());
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