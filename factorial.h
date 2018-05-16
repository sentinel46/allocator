#pragma once

constexpr auto factorial(auto n) -> decltype(n)
{
    return n ? n * factorial(n - 1) : 1;
}
