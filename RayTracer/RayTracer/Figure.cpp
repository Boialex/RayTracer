#include "Figure.h"

IFigure * createFigure(figure_type type, const double reflect, const double refract,
    const Color color, const Point3D first, ...)
{
    if (type == ht_sphere) {
        double r;
        va_list args;
        va_start(args, first);
        r = va_arg(args, double);
        va_end(args);
        return new Sphere(reflect, refract, color, first, r);
    }
    double x1, x2, y1, y2, z1, z2;
    va_list args;
    va_start(args, first);
    x1 = va_arg(args, double);
    y1 = va_arg(args, double);
    z1 = va_arg(args, double);
    x2 = va_arg(args, double);
    y2 = va_arg(args, double);
    z2 = va_arg(args, double);
    
    if (type == ht_triangle) {
        va_end(args);
        return new Triangle(reflect, refract, color, first, Point3D(x1, y1, z1), Point3D(x2, y2, z2));
    }

    double x3, y3, z3;
    x3 = va_arg(args, double);
    y3 = va_arg(args, double);
    z3 = va_arg(args, double);
    va_end(args);

    if (type == ht_quadrangle) {
        return new Quadrangle(reflect, refract, color, first, Point3D(x1, y1, z1), 
                               Point3D(x2, y2, z2), Point3D(x3, y3, z3));
    }
    return NULL;
}