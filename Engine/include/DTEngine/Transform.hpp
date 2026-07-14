#ifndef DTENGINE_TRANSFORM_H
#define DTENGINE_TRANSFORM_H

#include <DTEngine/Component.hpp>

#include <vector>

namespace DTEngine
{

class Transform : public Component
{
friend class GameObject;

public:
	virtual ~Transform();
	Transform(GameObject& _gameObject);

	// Handle to this transform's own slot in the pool
	EntityHandle<Transform> GetHandle() const;

	// An invalid handle makes the transform a root (no parent)
	void SetParent(const EntityHandle<Transform>& newParent);
	EntityHandle<Transform> GetParent() const;

	int ChildCount();
	EntityHandle<Transform> ChildAt(int position);
	bool HasChild(const EntityHandle<Transform>& obj, int& outPosition);

	//
	// World-space transform, composed up the parent hierarchy.
	// For root objects it equals the local fields.
	// Virtual so derived transforms (e.g. UI) can redefine the composition
	//

	virtual void SetPosition(const Vector2& position);
	virtual Vector2 GetPosition() const;

	virtual void SetScale(const Vector2& scale);
	virtual Vector2 GetScale() const;

	virtual void SetRotation(float rotation);
	virtual float GetRotation() const;

public:
	// Local to the parent; equals world space for root objects
	Vector2 localPosition;
	Vector2 localScale;
	float localRotation;

private:
	void AddChild(const EntityHandle<Transform>& obj);
	void RemoveChild(const EntityHandle<Transform>& obj);

	// Drops invalidated child handles
	void PruneChildren();

private:
	EntityHandle<Transform> parent;
	std::vector<EntityHandle<Transform>> children;

};

}

#endif
