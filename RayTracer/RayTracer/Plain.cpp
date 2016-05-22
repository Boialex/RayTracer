#include "Plain.h"

Plane::Plane(long double A, long double B, long double C, long double D)
{
    long double sq = sqrt(A * A + B * B + C * C);
    _A = A / sq;
    _B = B / sq;
    _C = C / sq;
    _D = D / sq;
}

Plane::Plane(const Triangle & triangle)
{
    Point3D n = triangle.normal();
    _A = n.x();
    _B = n.y();
    _C = n.z();
    Point3D a = triangle.A();
    _D = -_A * a.x() - _B * a.y() - _C * a.z();
}

Plane::Plane(const Quadrangle & quad)
{
    Point3D n = quad.normal();
    _A = n.x();
    _B = n.y();
    _C = n.z();
    Point3D a = quad.A();
    _D = -_A * a.x() - _B * a.y() - _C * a.z();
}

Point3D Plane::normal() const
{
    return Point3D(_A, _B, _C);
}

long double Plane::distance(const Point3D & p)
{
    return _A * p.x() + _B * p.y() + _C * p.z() + _D;
}

bool Plane::rayIntersect(const Ray & ray, Point3D & intersection)
{
    Point3D n = normal();
    if (fabs(n * ray.a()) <= EPS)
        return false;
    Point3D x;
    long double t = -(_D + _A * ray.r0().x() + _B * ray.r0().y() + _C * ray.r0().z()) / 
                     (_A * ray.a().x() + _B * ray.a().y() + _C * ray.a().z());
    intersection = ray.r0() + ray.a() * t;
    if ((intersection - ray.r0()) * ray.a() > 0)
        return true;
    return false;
}

