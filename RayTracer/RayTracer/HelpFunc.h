#pragma once
#include <algorithm>

bool isZero(const double a);

long double min(long double a, long double b);
long double min(long double a);

long double max(long double a, long double b);
long double max(long double a);

template <typename... Args>
long double min(long double a, Args ... args)
{
    return std::min(a, min(args...));
}

template <typename... Args>
long double max(long double a, Args ... args)
{
    return std::max(a, max(args...));
}


