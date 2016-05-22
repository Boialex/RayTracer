#include "Sphere.h"

Sphere::Sphere(const double reflect, const double refract, const Color color, const Point3D O, const double r)
{
    _reflect = reflect;
    _refract = refract;
    _color = color;
    _r = r;
    _O = O;
}

double Sphere::r() const
{
    return _r;
}

Point3D Sphere::O() const
{
    return _O;
}

double Sphere::reflect() const
{
    return _reflect;
}

double Sphere::refract() const
{
    return _refract;
}

Color Sphere::color() const
{
    return _color;
}

void Sphere::setRadius(const double r)
{
    _r = r;
}

void Sphere::setCenter(const Point3D O)
{
    _O = O;
}

void Sphere::setParams(const double reflect, const double refract, const Color color)
{
    _reflect = reflect;
    _refract = refract;
    _color = color;
}

bool Sphere::rayIntersect(const Ray & ray, IntersectionData & data)
{
    if (ray.r0() == _O) {
        data.intersection = _O + ray.a() * _r;
        data.obj = this;
        data.intersects = true;
        return true;
    }
    Point3D s = _O - ray.r0();
    double cos = ray.a() * s / s.len();
    double D = pow(2 * s.len() * cos, 2) - 4 * (s.len() * s.len() - _r * _r);
    if (D < 0)
        return false;
    if (D == 0) {
        double x = s.len() * cos;
        data.intersection = ray.r0() + ray.a() * x;
        data.obj = this;
        data.intersects = true;
        return true;
    }
    double x1 = s.len() * cos - sqrt(D) / 2;
    double x2 = s.len() * cos + sqrt(D) / 2;
    if (x1 < 0)
        if (x2 < 0)
            return false;
        else {
            data.intersection = ray.r0() + ray.a() * x2;
            data.obj = this;
            data.intersects = true;
            return true;
        }
    else {
        data.intersection = ray.r0() + ray.a() * x1;
        data.obj = this;
        data.intersects = true;
        return true;
    }
    return false;
}

Box Sphere::getBox() const
{
    double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = _O.x() - _r;
    xmax = _O.x() + _r;
    ymin = _O.y() - _r;
    ymax = _O.y() + _r;
    zmin = _O.z() - _r;
    zmax = _O.z() + _r;
    if (isZero(xmax - xmin)) {
        xmax += EPS;
        xmin -= EPS;
    }
    if (isZero(ymax - ymin)) {
        ymax += EPS;
        ymin -= EPS;
    }
    if (isZero(zmax - zmin)) {
        zmax += EPS;
        zmin -= EPS;
    }
    return Box(Point3D(xmin, ymin, zmin), Point3D(xmax, ymax, zmax));
}

Point3D Sphere::normal(const Point3D & p) const
{
    Point3D n = p - _O;
    return n * (1.0 / n.len());
}

