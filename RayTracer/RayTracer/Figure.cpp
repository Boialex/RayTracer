#include "Figure.h"
#include <algorithm>


long double min(long double a, long double b)
{
    return std::min(a, b);
}

long double min(long double a)
{
    return a;
}

template <typename... Args>
long double min(long double a, Args ... args) 
{
    return min(a, min(args...));
}

long double max(long double a, long double b)
{
    return std::max(a, b);
}

long double max(long double a)
{
    return a;
}

template <typename... Args>
long double max(long double a, Args ... args)
{
    return max(a, max(args...));
}

IFigure * createFigure(figure_type type, const long double reflection, const long double refraction,
    const Color color, const Point3D first, ...)
{
    if (type == ht_sphere) {
        long double r;
        va_list args;
        va_start(args, first);
        r = va_arg(args, long double);
        va_end(args);
        return new Sphere(reflection, refraction, color, first, r);
    }
    long double x1, x2, y1, y2, z1, z2;
    va_list args;
    va_start(args, first);
    x1 = va_arg(args, long double);
    y1 = va_arg(args, long double);
    z1 = va_arg(args, long double);
    x2 = va_arg(args, long double);
    y2 = va_arg(args, long double);
    z2 = va_arg(args, long double);
    
    if (type == ht_triangle) {
        va_end(args);
        return new Triangle(reflection, refraction, color, first, Point3D(x1, y1, z1), Point3D(x2, y2, z2));
    }

    long double x3, y3, z3;
    x3 = va_arg(args, long double);
    y3 = va_arg(args, long double);
    z3 = va_arg(args, long double);
    va_end(args);

    if (type == ht_parallelogramm) {
        return new Parallelogramm(reflection, refraction, color, first, Point3D(x1, y1, z1), 
                                   Point3D(x2, y2, z2), Point3D(x3, y3, z3));
    }
    if (type == ht_quadrangle) {
        return new Quadrangle(reflection, refraction, color, first, Point3D(x1, y1, z1), 
                               Point3D(x2, y2, z2), Point3D(x3, y3, z3));
    }
    return NULL;
}