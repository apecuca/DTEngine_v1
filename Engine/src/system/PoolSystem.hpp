#ifndef DTENGINE_POOLSYSTEM_H
#define DTENGINE_POOLSYSTEM_H

#include "system/InternalSystem.hpp"

#include <DTEngine/Entity.hpp>
#include <DTEngine/EntityHandle.hpp>

#include <memory>
#include <deque>

namespace DTEngine
{

class PoolSystem : public InternalSystem
{
friend class SystemRegistry;

public:
    ~PoolSystem();
    PoolSystem();

    // Non-template core: stores the entity in a free slot (or a new one)
    // and returns a type-erased reference to it
    EntitySlotRef Acquire(std::unique_ptr<Entity> entity);

    // Frees the slot holding the entity and bumps its generation,
    // invalidating every handle that points to it
    void Release(Entity* entity);

    template <typename T, typename... Args>
    EntityHandle<T> PoolEntity(Args&&... args)
    {
        static_assert(std::derived_from<T, Entity>);
        static_assert(std::constructible_from<T, Args...>,
           "T has no compatible constructor with passed parameters");

        return EntityHandle<T>(Acquire(std::make_unique<T>(std::forward<Args>(args)...)));
    }

    template <typename T>
    void DeleteEntity(EntityHandle<T>& handle)
    {
        // Bypasses the handle's marked-for-destruction check: a marked
        // entity still owns its slot and must be releasable
        if (handle.ref.IsAlive())
            Release(handle.ref.ptr);
    }

protected:
    bool Init() override;

    struct EntitySlot
    {
       std::unique_ptr<Entity> entity;
       uint32_t generation = 0;
    };

    std::deque<EntitySlot> entityPool;

    // Entities destroyed during pool teardown may call Release re-entrantly
    // while entityPool is being cleared
    bool shuttingDown = false;

};

}

#endif