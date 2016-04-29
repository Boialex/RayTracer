#include "Sphere.h"

Sphere::Sphere(const long double reflection, const long double refraction, const Color color, const Point3D O, const long double r)
{
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
    _r = r;
    _O = O;
}

long double Sphere::r() const
{
    return _r;
}

Point3D Sphere::O() const
{
    return _O;
}

long double Sphere::reflection() const
{
    return _reflection;
}

long double Sphere::refraction() const
{
    return _refraction;
}

Color Sphere::color() const
{
    return _color;
}

void Sphere::setRadius(const long double r)
{
    _r = r;
}

void Sphere::setCenter(const Point3D O)
{
    _O = O;
}

void Sphere::setParams(const long double reflection, const long double refraction, const Color color)
{
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
}

bool Sphere::rayIntersect(const Ray & ray, Point3D & intersect) const
{
    if (ray.r0() == _O) {
        intersect = _O + ray.a() * _r;
        return true;
    }
    Point3D s = _O - ray.r0();
    long double cos = ray.a() * s / s.len();
    long double D = pow(2 * s.len() * cos, 2) - 4 * (s.len() * s.len() - _r * _r);
    if (D < 0)
        return false;
    if (D == 0) {
        long double x = s.len() * cos;
        intersect = ray.r0() + ray.a() * x;
        return true;
    }
    long double x1 = s.len() * cos - sqrt(D) / 2;
    long double x2 = s.len() * cos + sqrt(D) / 2;
    if (x1 < 0)
        if (x2 < 0)
            return false;
        else {
            intersect = ray.r0() + ray.a() * x2;
            return true;
        }
    else {
        intersect = ray.r0() + ray.a() * x1;
        return true;
    }
    return false;
}

Box Sphere::getBox() const
{
    long double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = _O.x() - _r;
    xmax = _O.x() + _r;
    ymin = _O.y() - _r;
    ymax = _O.y() + _r;
    zmin = _O.z() - _r;
    zmax = _O.z() + _r;
    Box b;
    b.A = Point3D(xmin, ymin, zmin);
    b.B = Point3D(xmax, ymax, zmax);
    return b;
}

Point3D Sphere::normal(const Point3D & p) const
{
    Point3D n = p - _O;
    return n * (1.0 / n.len());
}

