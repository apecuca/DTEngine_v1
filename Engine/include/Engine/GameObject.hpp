#ifndef DTENGINE_GAMEOBJECT_H
#define DTENGINE_GAMEOBJECT_H

#include "Entity.hpp"
#include "Component.hpp"
#include <memory>

namespace DTEngine
{

class World;
class Component;

class GameObject : public Entity
{
friend class World;

public:
    virtual ~GameObject();
    GameObject();

public:
    void SetParent(GameObject* obj);
    GameObject* GetParent();

    //
    // Component logic
    //

    template <typename T>
    requires std::derived_from<T, Component>
    T* AddComponent()
    {
        if (GetComponent<T>() != nullptr) {
            std::string msg = "GameObject already has component of type ";
            msg += typeid(T).name();
            throw std::string(msg);
        }

        std::unique_ptr<T> newComponent = std::make_unique<T>(*this);
        T* rawPtr = static_cast<T*>(newComponent.get());
        components.push_back(std::move(newComponent));

        return rawPtr; 
    }

    template <typename T>
    requires std::derived_from<T, Component>
    T* GetComponent()
    {
        for (auto& component : components)
            if (typeid(*component) == typeid(T))
                return dynamic_cast<T*>(component.get());

        return nullptr;
    }

    template <typename T>
    requires std::derived_from<T, Component>
    const T* GetComponent() const
    {
        for (const auto& component : components)
            if (typeid(*component) == typeid(T))
                return dynamic_cast<T*>(component.get());

        return nullptr;
    }

    template <typename T>
    requires std::derived_from<T, Component>
    void RemoveComponent()
    {
        Component* ptr = GetComponent<T>();
        if (ptr == nullptr) {
            std::string msg = "GameObject has no component of type ";
            msg += typeid(T).name();
            throw std::string(msg);
        }

        for (int i = 0; i < components.size(); i++) {
            if (components[i].get() != ptr)
                continue;

            components[i]->markedForDestruction = true;
            return;
        }

        std::string errMsg = "Err on removing component from GameObject of id ";
        errMsg += std::to_string(GetID());
        throw std::string(errMsg);
    }

private:
    // Marks object to be destroyed on the end of the current frame
    void MarkForDestruction();

    // Destroy all components marked for destruction
    void ProcessComponentDestructionQueue();

    // Returns if the object is marked to be destroyed
    bool GetMarkedForDestruction() const;

    void AddChild(GameObject* obj);
    void RemoveChild(GameObject* obj);
    bool HasChild(GameObject* obj, int& outPosition);

    void InternalStart();
    void InternalUpdate();

public:
    Vector2 position;
    Vector2 scale;
    GameObject* parent;

private:
    bool markedForDestruction = false;
    
    GameObject* originalParent;
    std::vector<GameObject*> children;

    std::vector< std::unique_ptr<Component> > components;
};

}

#endif