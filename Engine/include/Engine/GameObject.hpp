#ifndef INCLUDED_GAMEOBJECT_H
#define INCLUDED_GAMEOBJECT_H

#include "Entity.hpp"

namespace DTEngine
{

class GameObject : public Entity
{
public:
    ~GameObject();
    GameObject();

public:
    // Marks object to be destroyed on the end of the current frame
    void MarkForDestruction();

    // Returns if the object is marked to be destroyed
    bool GetMarkedForDestruction() const;

public:
    Vector2 position;

private:
    bool markedForDestruction;

    GameObject* parent;
    std::vector<GameObject*> children;

};

}

#endif