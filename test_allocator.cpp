#define BOOST_TEST_MODULE test_allocator

#include "newdelete.h"

#include <boost/test/included/unit_test.hpp>

#include "allocator.h"
#include "factorial.h"
#include "linkedlist.h"

BOOST_AUTO_TEST_SUITE(test_allocator_suite)

BOOST_AUTO_TEST_CASE(test_factorial_function)
{
    BOOST_CHECK(factorial(0) ==                 1);
    BOOST_CHECK(factorial(1) ==                 1);
    BOOST_CHECK(factorial(2) ==               2*1);
    BOOST_CHECK(factorial(3) ==             3*2*1);
    BOOST_CHECK(factorial(4) ==           4*3*2*1);
    BOOST_CHECK(factorial(5) ==         5*4*3*2*1);
    BOOST_CHECK(factorial(6) ==       6*5*4*3*2*1);
    BOOST_CHECK(factorial(7) ==     7*6*5*4*3*2*1);
    BOOST_CHECK(factorial(8) ==   8*7*6*5*4*3*2*1);
    BOOST_CHECK(factorial(9) == 9*8*7*6*5*4*3*2*1);
}

BOOST_AUTO_TEST_CASE(test_my_allocator)
{
    my::allocator<int, 10> allocator;

    auto ptr = allocator.allocate(1);
    BOOST_CHECK(ptr != nullptr);

    allocator.deallocate(ptr, 1);
}

BOOST_AUTO_TEST_CASE(test_my_linkedlist)
{
    my::LinkedList<int, my::allocator<int, 10>> container;
    for (auto i = 0; i < 10; ++i)
        container.push_back(i);

    auto counter = 0;
    for (auto item: container) {
        BOOST_CHECK(item == counter);
        ++counter;
    }
}

BOOST_AUTO_TEST_CASE(test_allocation_count)
{
    auto before = my::alloc_counter;
    my::LinkedList<int, my::allocator<int, 10>> container;
    for (auto i = 0; i < 10; ++i)
        container.push_back(i);
    auto after = my::alloc_counter;

    BOOST_CHECK((after - before) <= 2);
}

BOOST_AUTO_TEST_SUITE_END()
