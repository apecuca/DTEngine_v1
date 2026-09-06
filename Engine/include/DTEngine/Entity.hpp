#ifndef DTENGINE_ENTITY_H
#define DTENGINE_ENTITY_H

#include <DTEngine/Utils.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <cstdint>
#include <vector>

namespace DTEngine
{

class Entity
{
template <typename T>
friend struct EntityHandle;
friend class PoolSystem;

public:
    using ID = std::uint32_t;

    virtual ~Entity();
    Entity();

    bool operator == (const Entity& other) const {
        return id == other.GetID();
    }

    ID GetID() const { return id; }

    // True from the moment the entity is destroyed until 
    // its slot is freed at the end of the frame
    bool IsMarkedForDestruction() const { return markedForDestruction; }

protected:
    bool markedForDestruction = false;
    ID id;

    // Reference to this entity's own slot in the PoolSystem; empty for
    // entities that live outside the pool
    EntitySlotRef selfRef;

    static ID nextID;
    static std::vector<ID> freeIDs;
};

}

#endif