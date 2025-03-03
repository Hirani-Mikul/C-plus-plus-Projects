#pragma once
#include <iostream>

int f(int x)
{
    if (x == 0) return 0;

    int result = 2 * f(x - 1) + x * x;

    return result;
}

int bad(int x)
{
    if (x == 0) return 0;

    return bad(x / 3 + 1) + x - 1;
}

void printNum(int x)
{
    if (x >= 10) printNum(x / 10);

    std::cout << x % 10;
}