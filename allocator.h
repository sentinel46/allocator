#pragma once

#include "newdelete.h"
#include <array>
#include <memory>
#include <vector>

namespace my
{

template <typename T, size_t capacity = 64>
class allocator
{
    static_assert(capacity != 0, "no zero capacity!");

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;

    template <class U>
    struct rebind
    {
        using other = allocator<U, capacity>;
    };

    allocator() = default;
    template<class U>
    allocator(const allocator<U, capacity> &other) {}

    T * allocate(size_t n)
    {
       if (n != 1)
           throw std::invalid_argument("Invalid numbers of elemens for allocate()");

       _pool.resize(1 + _index / capacity);
       _pool[_index/capacity].resize(capacity);
       T *p = reinterpret_cast<T*>(&_pool[_index/capacity][_index%capacity]);
       _index += n;
       return p;
    }

    void deallocate(T*, size_t) {}

    template<typename U, typename ... Args>
    void construct(U *p, Args&&... args)
    {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p)
    {
        p->~T();
    }

private:
    //std::vector<std::array<T, capacity>> _pool;  // T() будет вызван capacity раз
    std::vector<std::vector<std::array<unsigned char, sizeof(T)>>> _pool;
    size_t _index = 0;
};

}
