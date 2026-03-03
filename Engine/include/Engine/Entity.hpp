#ifndef DTENGINE_ENTITY_H
#define DTENGINE_ENTITY_H

#include <cstdint>
#include <vector>

#include "Engine/Utils.hpp"

namespace DTEngine
{
    
class Entity
{
public:
    using ID = std::uint32_t;

    virtual ~Entity();
    Entity();

    bool operator == (const Entity& other) const {
        return id == other.GetID();
    }

    ID GetID() const { return id; }

protected:
    ID id;

    static ID nextID;
    static std::vector<ID> freeIDs;
};

}

#endif