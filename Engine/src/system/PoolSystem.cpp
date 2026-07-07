#include "system/PoolSystem.hpp"

using namespace DTEngine;

PoolSystem::~PoolSystem()
{
    shuttingDown = true;
    entityPool.clear();
}

PoolSystem::PoolSystem()
{
    entityPool = std::deque<EntitySlot>{};
}

bool PoolSystem::Init()
{
    return true;
}

EntitySlotRef PoolSystem::Acquire(std::unique_ptr<Entity> entity)
{
    EntitySlot* slot = nullptr;
    for (auto& s : entityPool) {
        if (s.entity == nullptr) {
            slot = &s;
            break;
        }
    }

    if (slot == nullptr) {
        entityPool.emplace_back();
        slot = &entityPool.back();
    }

    slot->entity = std::move(entity);

    EntitySlotRef ref;
    ref.ptr = slot->entity.get();
    ref.generation = &(slot->generation);
    ref.expectedGeneration = slot->generation;

    slot->entity->selfRef = ref;

    return ref;
}

void PoolSystem::Release(Entity* entity)
{
    if (shuttingDown || entity == nullptr)
        return;

    for (auto& slot : entityPool) {
        if (slot.entity.get() == entity) {
            slot.entity.reset();
            ++slot.generation;
            return;
        }
    }
}
