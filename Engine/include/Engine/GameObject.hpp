#ifndef DTENGINE_GAMEOBJECT_H
#define DTENGINE_GAMEOBJECT_H

#include "Entity.hpp"

namespace DTEngine
{

class World;

class GameObject : public Entity
{
friend class World;

public:
    virtual ~GameObject();
    GameObject();

public:
    void SetParent(GameObject* obj);
    GameObject* GetParent();

private:
    // Marks object to be destroyed on the end of the current frame
    void MarkForDestruction();

    // Returns if the object is marked to be destroyed
    bool GetMarkedForDestruction() const;

    void AddChild(GameObject* obj);
    void RemoveChild(GameObject* obj);
    bool HasChild(GameObject* obj, int& outPosition);

public:
    Vector2 position;
    Vector2 scale;
    GameObject* parent;

private:
    bool markedForDestruction;
    
    GameObject* originalParent;
    std::vector<GameObject*> children;

};

}

#endif