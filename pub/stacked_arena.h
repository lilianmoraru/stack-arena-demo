#ifndef STACK_ARENA_H
#define STACK_ARENA_H

#include <vector>
#include <utility> // std::move

namespace demo
{

template <typename T, size_t StackSize, size_t MiniArenaSize = 32>
class StackArena
{
    static_assert(StackSize     != 0, "StackSize cannot be 0");
    static_assert(MiniArenaSize != 0, "MiniArenaSize cannot be 0");

    // We'll do a pointer bump inside the stack and switch to heap when we reach the capacity limit
    T               stack[StackSize] {};

    // When we reach the stack size limit, we'll switch to heap allocated mini arenas,
    // where we will also bump the pointer up the "stack"
    std::vector<T*> heap             {};

    // Track the pointer position
    size_t          count            {};

public:
    ~StackArena()
    {
        for (T *const ptr : heap)
        {
            delete []ptr;
        }
    }

    // Do not allow obtaining pointers to a temporary Arena
    T* getNextPtr() &&       = delete;
    T* getNextPtr() const && = delete;
    T* getNextPtr(T&& initData) &&       = delete;
    T* getNextPtr(T&& initData) const && = delete;

    // Can pass StackArena as const&, but cannot get a new Ptr through it
    T* getNextPtr() const &              = delete;
    T* getNextPtr(T&& initData) const &  = delete;

    T* getNextPtr() &
    {
        return getPtr();
    }

    T* getNextPtr(const T& initData) &
    {
        T *const ptr = getPtr();
        *ptr = initData;

        return ptr;
    }

    T* getNextPtr(T&& initData) &
    {
        T *const ptr = getPtr();
        *ptr = std::move(initData);

        return ptr;
    }

    size_t size() const noexcept
    {
        return count;
    }

private:
    T* getPtr()
    {
        // Are we still on the stack?(the most likely "branch" first)
        const bool isOnStack = count < StackSize;
        if (isOnStack)
        {
            const size_t currentPos = count;
            count++;

            return &stack[currentPos];
        }

        // Here we are starting to work with the heap
        const size_t currentHeapPos = count - StackSize;
        const size_t bucket = currentHeapPos / MiniArenaSize;
        const size_t currentMiniHeapPos = (currentHeapPos == 0) ? 0 : currentHeapPos % MiniArenaSize;

        if (currentMiniHeapPos == 0)
        {
            heap.resize(bucket + 1);
            heap[bucket] = new T[MiniArenaSize];
        }

        T *const miniArenaPtr = heap[bucket];

        count++;
        return &miniArenaPtr[currentMiniHeapPos];
    }
};

} // namespace demo

#endif // STACK_ARENA_H