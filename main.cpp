#include <iostream>
#include <map>
#include <algorithm>

#include "allocator.h"
#include "linkedlist.h"

constexpr auto factorial(auto n) -> decltype(n)
{
    return n ? n * factorial(n - 1) : 1;
}

static_assert(factorial(9) == 9*8*7*6*5*4*3*2*1, "factorial failed!");
static_assert(factorial(8) ==   8*7*6*5*4*3*2*1, "factorial failed!");
static_assert(factorial(7) ==     7*6*5*4*3*2*1, "factorial failed!");
static_assert(factorial(6) ==       6*5*4*3*2*1, "factorial failed!");
static_assert(factorial(5) ==         5*4*3*2*1, "factorial failed!");
static_assert(factorial(4) ==           4*3*2*1, "factorial failed!");
static_assert(factorial(3) ==             3*2*1, "factorial failed!");
static_assert(factorial(2) ==               2*1, "factorial failed!");
static_assert(factorial(1) ==                 1, "factorial failed!");
static_assert(factorial(0) ==                 1, "factorial failed!");

template <typename T>
void usingStlContainerWithStlAllocator(T &&generator)
{
    std::map<int, int> container;
    std::generate_n(std::inserter(container, std::begin(container)), 10, generator);

    for (const auto &item: container)
        std::cout << item.first << " " << item.second << std::endl;
}

template <typename T>
void usingStlContainerWithCustomAllocator(T &&generator)
{
    std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>, 10>> container;
    std::generate_n(std::inserter(container, std::begin(container)), 10, generator);

    for (const auto &item: container)
        std::cout << item.first << " " << item.second << std::endl;
}

void usingCustomContainerWithStlAllocator()
{
    my::LinkedList<int> container;
    for (auto i = 0; i < 10; ++i)
        container.append(factorial(i));

    for (const auto &item: container)
        std::cout << item << std::endl;
}

void usingCustomContainerWithCustomAllocator()
{
    my::LinkedList<int, my::allocator<int, 10>> container;
    for (auto i = 0; i < 10; ++i)
        container.append(factorial(i));

    for (const auto& item: container)
        std::cout << item << std::endl;
}

int main()
{
//    std::cout << "-------------- my::alloc_counter=" << my::alloc_counter << std::endl;

    auto makeFactorialValue = [i=0]() mutable {
        auto f = factorial(i);
        auto value = std::make_pair(i, f);
        ++i;
        return value;
    };

    try {
        usingStlContainerWithStlAllocator(makeFactorialValue);
        usingStlContainerWithCustomAllocator(makeFactorialValue);
        usingCustomContainerWithStlAllocator();
        usingCustomContainerWithCustomAllocator();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

//    std::cout << "-------------- my::alloc_counter=" << my::alloc_counter << std::endl;

    return 0;
}
