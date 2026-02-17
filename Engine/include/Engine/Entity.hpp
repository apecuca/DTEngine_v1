#ifndef INCLUDED_ENTITY_H
#define INCLUDED_ENTITY_H

#include <cstdint>
#include <vector>

namespace DTEngine
{
    
class Entity
{
public:
    using ID = std::uint64_t;

    ~Entity();
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