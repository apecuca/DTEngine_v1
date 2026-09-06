#ifndef DTENGINE_GAMEOBJECT_H
#define DTENGINE_GAMEOBJECT_H

#include <DTEngine/Entity.hpp>

#include <DTEngine/Transform.hpp>
#include <DTEngine/EntityHandle.hpp>
#include <DTEngine/Utils.hpp>

#include <memory>
#include <stdexcept>
#include <ostream>
#include <typeinfo>
#include <vector>

namespace DTEngine
{

class World;
struct Collision;

class GameObject : public Entity
{
friend class World;
friend class PhysicsSystem;

public:
    virtual ~GameObject();
    GameObject(std::string _name);

public:
    // Handle to this object's own slot in the pool; invalid for objects
    // that live outside the pool (e.g. the World itself)
    EntityHandle<GameObject> GetHandle() const;

    void SetLayer(const std::string& layerName);
    std::string GetLayer() const;

    //
    // Component logic
    //

    template <typename T>
    EntityHandle<T> AddComponent()
    {
        static_assert(std::derived_from<T, Component>);

        return EntityHandle<T>(AddComponentImpl(std::make_unique<T>(*this)));
    }

    template <typename T>
    EntityHandle<T> GetComponent()
    {
        static_assert(std::derived_from<T, Component>);

        return EntityHandle<T>(FindComponentImpl(typeid(T)));
    }

    template <typename T>
    EntityHandle<T> GetComponent() const
    {
        static_assert(std::derived_from<T, Component>);

        return const_cast<GameObject*>(this)->GetComponent<T>();
    }

    template <typename T>
    void RemoveComponent()
    {
        static_assert(std::derived_from<T, Component>);

        T* component = GetComponent<T>().Get();
        if (component == nullptr) {
            std::string msg = "GameObject has no component of type ";
            msg += typeid(T).name();
            throw std::runtime_error(msg);
        }

        component->markedForDestruction = true;
        component->OnMarkedForDestruction();
    }

private:
    // Marks object to be destroyed on the end of the current frame
    void MarkForDestruction();

    // Destroy all components marked for destruction
    void ProcessComponentDestructionQueue();

    // Non-template bridges to the PoolSystem, implemented in the .cpp so
    // the public header stays free of internal system includes
    EntitySlotRef AddComponentImpl(std::unique_ptr<Component> component);
    EntitySlotRef FindComponentImpl(const std::type_info& type) const;

    void InternalAwake();
    void InternalStart();
    void InternalFixedUpdate();
    void InternalUpdate();
    void InternalLateUpdate();

    void ReceiveCollisionMessage(Collision& collision);
    void ReceiveSensorMessage(Collision& collision);

public:
    EntityHandle<Transform> transform;

    bool clickable;
    std::string tag;
    std::string name;

private:
    std::string layer;

    // References to this object's components inside the PoolSystem
    std::vector<EntitySlotRef> componentRefs;
};

}

#endif