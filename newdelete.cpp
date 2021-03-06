#include "newdelete.h"

#include <cstdio>
#include <cstdlib>

namespace my
{
size_t alloc_counter = 0;

void * malloc(size_t size) throw (std::bad_alloc)
{
    void *p = std::malloc(size);
    printf("malloc: %zu %p %zu\n", ++alloc_counter, p, size);
    return p;
}

void free(void *p) noexcept
{
    printf("free: %zu %p\n", --alloc_counter, p);
    std::free(p);
    return;
}

}   // namespace my
