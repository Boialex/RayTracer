#pragma once

#include "Figure.h"
//#include "HelpFunc.h"

class Plane {
public:
    Plane(long double A, long double B, long double C, long double D);
    Plane(const Triangle & triangle);
    Plane(const Quadrangle & quad);

    Point3D normal() const;
    long double distance(const Point3D & p);

    bool rayIntersect(const Ray & ray, Point3D & intersection);

private:
    long double _A, _B, _C, _D;
};
