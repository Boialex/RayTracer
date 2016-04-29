#include "Quadrangle.h"
#include "Plain.h"

Quadrangle::Quadrangle(const long double reflection, const long double refraction, const Color color,
    const Point3D A, const Point3D B, const Point3D C, const Point3D D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
}

Point3D Quadrangle::A() const
{
    return _A;
}

Point3D Quadrangle::B() const
{
    return _B;
}


Point3D Quadrangle::C() const
{
    return _C;
}

Point3D Quadrangle::D() const
{
    return _D;
}

long double Quadrangle::reflection() const
{
    return _reflection;
}

long double Quadrangle::refraction() const
{
    return _refraction;
}

Color Quadrangle::color() const
{
    return _color;
}

void Quadrangle::setA(const Point3D A)
{
    _A = A;
}

void Quadrangle::setB(const Point3D B)
{
    _B = B;
}

void Quadrangle::setC(const Point3D C)
{
    _C = C;
}

void Quadrangle::setD(const Point3D D)
{
    _D = D;
}

void Quadrangle::setPoints(const Point3D A, const Point3D B, const Point3D C, const Point3D D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
}

void Quadrangle::setParams(const long double reflection, const long double refraction, const Color color)
{
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
}

bool Quadrangle::rayIntersect(const Ray & ray, Point3D & intersect) const
{
    Point3D A = _A;
    Point3D B = _B;
    Point3D C = _C;
    Point3D D = _D;
    Point3D n = normal();
    Plane myPlane(*this);
    if (myPlane.rayIntersect(ray, intersect)) {
        if (((B - A) ^ (intersect - A)) * n < 0)
            return false;
        if (((A - D) ^ (intersect - D)) * n < 0)
            return false;
        if (((C - B) ^ (intersect - B)) * n < 0)
            return false;
        if (((D - C) ^ (intersect - C)) * n < 0)
            return false;
        return true;
    }
    return false;
}

Point3D Quadrangle::normal(const Point3D & p) const
{
    Point3D A = Point3D(_A);
    Point3D B = Point3D(_B);
    Point3D C = Point3D(_C);
    Point3D n = (B - A) ^ (C - A);
    return n * (1.0 / n.len());
}

Box Quadrangle::getBox() const
{
    long double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = min(_A.x(), _B.x(), _C.x(), _D.x());
    xmax = max(_A.x(), _B.x(), _C.x(), _D.x());
    ymin = min(_A.y(), _B.y(), _C.y(), _D.y());
    ymax = max(_A.y(), _B.y(), _C.y(), _D.y());
    zmin = min(_A.z(), _B.z(), _C.z(), _D.z());
    zmax = max(_A.z(), _B.z(), _C.z(), _D.z());
    Box b;
    b.A = Point3D(xmin, ymin, zmin);
    b.B = Point3D(xmax, ymax, zmax);
    return b;
}


