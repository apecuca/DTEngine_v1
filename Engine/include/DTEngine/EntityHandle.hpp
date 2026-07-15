#ifndef DTENGINE_ENTITYHANDLE_H
#define DTENGINE_ENTITYHANDLE_H

#include <cassert>
#include <concepts>
#include <cstddef>
#include <cstdint>

namespace DTEngine
{

class Entity;

// Type-erased reference to a pooled entity slot. Bridges the public
// headers and the internal PoolSystem without exposing it.
struct EntitySlotRef
{
    Entity* ptr = nullptr;
    uint32_t* generation = nullptr;
    uint32_t expectedGeneration = 0;

    bool IsAlive() const { return ptr != nullptr && *generation == expectedGeneration; }
};

template<typename T>
struct EntityHandle
{
friend class PoolSystem;

public:
    EntityHandle() = default;
    explicit EntityHandle(EntitySlotRef ref) : ref(ref) {}

    EntityHandle(std::nullptr_t) : EntityHandle() {}

    // A handle is valid while its slot keeps the same generation and the
    // entity is not queued for destruction. The cast keeps the expression
    // dependent on T so Entity may still be incomplete here
    bool IsValid() const
    {
        return ref.IsAlive() && !static_cast<T*>(ref.ptr)->markedForDestruction;
    }

    T* Get() const
    {
        // Asserted here instead of at class scope so a class can hold a
        // handle to itself while still incomplete
        static_assert(std::derived_from<T, Entity>);

        return IsValid() ? static_cast<T*>(ref.ptr) : nullptr;
    }

    T* operator->() const
    {
        T* entity = Get();
        assert(entity != nullptr && "Accessing an invalid EntityHandle");
        return entity;
    }

    bool operator == (const EntityHandle& other) const
    {
        return Get() == other.Get();
    }

    bool operator == (std::nullptr_t) const
    {
        return !IsValid();
    }

    explicit operator bool() const
    {
        return IsValid();
    }

private:
    EntitySlotRef ref;
};

}

#endif
