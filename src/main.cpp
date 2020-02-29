#include <stacked_arena.h>

int main()
{
    demo::StackArena<int, 1> arena;
    int *const stackPtr = arena.getNextPtr(0);
    int *const heapPtr  = arena.getNextPtr();

    *heapPtr = 10;

    return *stackPtr * *heapPtr; // return 0; :)
}
