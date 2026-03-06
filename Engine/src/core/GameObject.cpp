#include <GameObject.hpp>

#include "World.hpp"
#include <algorithm>
#include "Component.hpp"

using namespace DTEngine;

GameObject::~GameObject()
{
    if (parent != nullptr)
        parent->RemoveChild(this);
}

GameObject::GameObject() :
    Entity(),
    originalParent(nullptr),
    parent(nullptr)
{
    //
}

void GameObject::MarkForDestruction()
{
    markedForDestruction = true;
}

void GameObject::ProcessComponentDestructionQueue()
{
    components.erase(
        std::remove_if(components.begin(), components.end(),
            [](const std::unique_ptr<Component>& comp)
            {
                return comp->markedForDestruction;
            }),
        components.end());
}

bool GameObject::GetMarkedForDestruction() const
{
    return markedForDestruction;
}

void GameObject::SetParent(GameObject* obj)
{
    if (originalParent == nullptr) {
        if (obj == nullptr)
            return;
        
        originalParent = obj;
        parent = originalParent;
    }
    else if (*obj == *parent)
        return;

    // Replace with world gameobject
    if (obj == nullptr)
        obj = originalParent;

    if (parent != nullptr)
        parent->RemoveChild(this);

    parent = obj;
    parent->AddChild(this);
}

GameObject* GameObject::GetParent()
{
    return parent;
}

void GameObject::AddChild(GameObject* obj)
{
    int position;
    if (HasChild(obj, position))
        return;

    children.emplace_back(obj);
}

void GameObject::RemoveChild(GameObject* obj)
{
    int position;
    if (!HasChild(obj, position))
        return;

    children.erase(children.begin() + position);
}

bool GameObject::HasChild(GameObject* obj, int& outPosition)
{
    outPosition = -1;

    for (int i = 0; i < children.size(); i++) {
        if (*children[i] == *obj) {
            outPosition = i;
            return true;
        }
    }

    return false;
} 

void GameObject::InternalStart()
{
    for (auto& comp : components)
        comp->Start();
}

void GameObject::InternalUpdate()
{
    for (auto& comp : components)
        comp->Update();
}