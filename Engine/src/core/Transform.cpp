#include <Transform.hpp>

#include <DTEngine/GameObject.hpp>

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace DTEngine;

namespace
{

// Division that degenerates to 0 instead of exploding on
// a near-zero parent scale
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

}

Transform::~Transform()
{
    //
}

Transform::Transform(GameObject& _gameObject) :
    Component(_gameObject),
    localPosition(0.0f, 0.0f),
    localScale(1.0f, 1.0f),
    localRotation(0.0f)
{
    //
}

EntityHandle<Transform> Transform::GetHandle() const
{
    return EntityHandle<Transform>(selfRef);
}

void Transform::SetParent(const EntityHandle<Transform>& newParent)
{
    Transform* target = newParent.Get();

    // Reject self-parenting and hierarchy cycles before mutating anything;
    // with cascading destruction a cycle would recurse forever
    for (Transform* ancestor = target; ancestor != nullptr; ancestor = ancestor->parent.Get()) {
        if (ancestor == this) {
            std::cerr << "[Transform] SetParent: would create a hierarchy cycle\n";
            return;
        }
    }

    if (parent == newParent)
        return;

    // Preserve the world transform across the reparent: the local values
    // are recomputed against the new parent so the object doesn't move
    Vector2 worldPosition = GetPosition();
    Vector2 worldScale = GetScale();
    float worldRotation = GetRotation();

    Transform* current = parent.Get();
    if (current != nullptr)
        current->RemoveChild(GetHandle());

    if (target == nullptr) {
        parent = EntityHandle<Transform>{};
    } else {
        parent = newParent;
        target->AddChild(GetHandle());
    }

    SetRotation(worldRotation);
    SetScale(worldScale);
    SetPosition(worldPosition);
}

EntityHandle<Transform> Transform::GetParent() const
{
    return parent;
}

void Transform::AddChild(const EntityHandle<Transform>& obj)
{
    int position;
    if (HasChild(obj, position))
        return;

    children.emplace_back(obj);
}

void Transform::RemoveChild(const EntityHandle<Transform>& obj)
{
    int position;
    if (!HasChild(obj, position))
        return;

    children.erase(children.begin() + position);
}

void Transform::PruneChildren()
{
    std::erase_if(children, [](const EntityHandle<Transform>& child) {
        return !child.IsValid();
    });
}

int Transform::ChildCount()
{
    PruneChildren();

    return static_cast<int>(children.size());
}

EntityHandle<Transform> Transform::ChildAt(int position)
{
    PruneChildren();

    if (position < 0 || position >= (int)children.size())
        throw std::runtime_error("Child position " + std::to_string(position) + " out of bounds");

    return children.at(position);
}

bool Transform::HasChild(const EntityHandle<Transform>& obj, int& outPosition)
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

Vector2 Transform::GetPosition() const
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr)
        return localPosition;

    // The local offset scales with the parent and orbits its pivot
    Vector2 offset = parentTransform->GetScale() * localPosition;
    offset.Rotate(parentTransform->GetRotation());

    return parentTransform->GetPosition() + offset;
}

void Transform::SetPosition(const Vector2& position)
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr) {
        localPosition = position;
        return;
    }

    Vector2 delta = position - parentTransform->GetPosition();
    delta.Rotate(-parentTransform->GetRotation());
    localPosition = SafeDiv(delta, parentTransform->GetScale());
}

Vector2 Transform::GetScale() const
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr)
        return localScale;

    return parentTransform->GetScale() * localScale;
}

void Transform::SetScale(const Vector2& scale)
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr) {
        localScale = scale;
        return;
    }

    localScale = SafeDiv(scale, parentTransform->GetScale());
}

float Transform::GetRotation() const
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr)
        return localRotation;

    return parentTransform->GetRotation() + localRotation;
}

void Transform::SetRotation(float rotation)
{
    Transform* parentTransform = parent.Get();
    if (parentTransform == nullptr) {
        localRotation = rotation;
        return;
    }

    localRotation = rotation - parentTransform->GetRotation();
}
