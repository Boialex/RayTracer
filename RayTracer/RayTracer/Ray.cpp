#include "Ray.h"

Ray::Ray(const Point3D r0, const Point3D b)
{
    _r0 = r0;
    _a = b - r0;
    _a = _a * (1.0 / _a.len());
}

Point3D Ray::r0() const
{
    return _r0;
}

Point3D Ray::a() const
{
    return _a;
}
