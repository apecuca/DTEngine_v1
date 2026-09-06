#include "Entity.hpp"

using namespace DTEngine;

Entity::ID Entity::nextID = 1;
std::vector<Entity::ID> Entity::freeIDs;

bool EntitySlotRef::IsLive() const
{
    return IsAlive() && !ptr->IsMarkedForDestruction();
}

Entity::Entity()
{
    if (!freeIDs.empty()) {
        id = freeIDs.back();
        freeIDs.pop_back();
    }
    else {
        id = nextID++;
    }
}

Entity::~Entity()
{
    freeIDs.push_back(id);
}