#include"HelpFunc.h"

bool isZero(const double a)
{
    if (fabs(a) < pow(10, -4))
        return true;
    return false;
}

long double min(long double a, long double b)
{
    return std::min(a, b);
}

long double min(long double a, long double b, long double c)
{
    return std::min(a, std::min(b, c));
}

long double min(long double a, long double b, long double c, long double d)
{
    return std::min(a, min(b, c, d));
}

long double min(long double a)
{
    return a;
}

long double max(long double a, long double b)
{
    return std::max(a, b);
}

long double max(long double a, long double b, long double c)
{
    return std::max(a, std::max(b, c));
}

long double max(long double a, long double b, long double c, long double d)
{
    return std::max(a, max(b, c, d));
}

long double max(long double a)
{
    return a;
}
