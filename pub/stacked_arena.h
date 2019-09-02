#include <vector>
#include <cstddef>

template <typename T, size_t StackSize, size_t MiniArenaSize = 32>
class Arena
{
    // We'll do a pointer bump inside the stack and switch to heap when we reach the capacity limit
    T                              stack[StackSize] {};

    // When we reach the stack size limit, we'll switch to heap allocated mini arenas,
    // where we will also bump the pointer up the "stack"
    std::vector<T*[MiniArenaSize]> heap             {};

    // Track the pointer position
    size_t                         count            {};

public:
    // Do not allow the user to take a pointer to a temporary stack/heap
    T* getPtr() &&       = delete;
    T* getPtr() const && = delete;

    T* getPtr() &
    { return nullptr; }

    // "const &" - a lie. Should be removed or make the internal data mutable
    T* getPtr() const &
    { return nullptr; }

    size_t size() const
    { return count; }
};
