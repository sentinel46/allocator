
#include "newdelete.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <iterator>
#include "allocator.h"
#include "vec.h"

constexpr auto factorial(auto n) -> decltype(n)
{
    return n ? n*factorial(n-1) : 1;
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

int main()
{
    std::cout << "-------------- my::alloc_counter=" << my::alloc_counter << std::endl;

    auto make_factorial_value = [i=0]() mutable
    {
        auto f = factorial(i);
        std::cout << i << " " << f << std::endl;
        auto value = std::make_pair(i,f);
        ++i;
        return value;
    };

    try
    {
        std::map<int, int> m1;
        std::generate_n(std::inserter(m1, std::begin(m1)),
                        15,
                        make_factorial_value);

        //for (const auto& p: m1)
        //    std::cout << p.first << " " << p.second << std::endl;

        std::cout << "-------------- my::alloc --------------\n";

        std::map<int, int, std::less<int>, my::allocator<std::pair<const int, int>, 10>> m2;
        std::generate_n(std::inserter(m2, std::begin(m2)),
                        15,
                        make_factorial_value);

        if (false)
        for (const auto& p: m2)
            std::cout << p.first << " " << p.second << std::endl;

        my::Vec<int> vec;
        vec.push_back(10);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "-------------- my::alloc_counter=" << my::alloc_counter << std::endl;

    return 0;
}
