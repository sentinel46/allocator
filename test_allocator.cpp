#define BOOST_TEST_MODULE test_allocator

#include "newdelete.h"

#include <boost/test/included/unit_test.hpp>

#include "allocator.h"
#include "linkedlist.h"

BOOST_AUTO_TEST_SUITE(test_allocator_suite)

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
        container.append(i);

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
        container.append(i);
    auto after = my::alloc_counter;

    BOOST_CHECK((after - before) <= 2);
}

BOOST_AUTO_TEST_SUITE_END()
