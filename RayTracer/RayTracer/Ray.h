#pragma once

#include "Point3D.h"

class Ray {
public:
    Ray() : _r0(), _a() {};
    Ray(const Point3D r0, const Point3D b);

    Point3D r0() const;
    Point3D a() const;

private:
    Point3D _r0;
    Point3D _a;
};                                                      