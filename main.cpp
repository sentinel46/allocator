#include <algorithm>
#include <iostream>
#include <map>

#include "allocator.h"
#include "factorial.h"
#include "linkedlist.h"

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
        container.push_back(factorial(i));

    for (const auto &item: container)
        std::cout << item << std::endl;
}

void usingCustomContainerWithCustomAllocator()
{
    my::LinkedList<int, my::allocator<int, 10>> container;
    for (auto i = 0; i < 10; ++i)
        container.push_back(factorial(i));

    for (const auto& item: container)
        std::cout << item << std::endl;
}

int main()
{
    auto makeFactorialValue = [i=0]() mutable {
        auto f = factorial(i);
        auto value = std::make_pair(i, f);
        ++i;
        return value;
    };

    try {
//        usingStlContainerWithStlAllocator(makeFactorialValue);
//        usingStlContainerWithCustomAllocator(makeFactorialValue);
        usingCustomContainerWithStlAllocator();
        usingCustomContainerWithCustomAllocator();
    }
    catch(const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
