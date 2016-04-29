#include "Triangle.h"
#include "Plain.h"
#include <>

Triangle::Triangle(const long double reflection, const long double refraction, const Color color, 
                    const Point3D A, const Point3D B, const Point3D C)
{
    _A = A;
    _B = B;
    _C = C;
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
}

Point3D Triangle::A() const
{
    return _A;
}

Point3D Triangle::B() const
{
    return _B;
}


Point3D Triangle::C() const
{
    return _C;
}

long double Triangle::reflection() const
{
    return _reflection;
}

long double Triangle::refraction() const
{
    return _refraction;
}

Color Triangle::color() const
{
    return _color;
}

void Triangle::setA(const Point3D A)
{
    _A = A;
}

void Triangle::setB(const Point3D B)
{
    _B = B;
}

void Triangle::setC(const Point3D C)
{
    _C = C;
}

void Triangle::setPoints(const Point3D A, const Point3D B, const Point3D C)
{
    _A = A;
    _B = B;
    _C = C;
}

void Triangle::setParams(const long double reflection, const long double refraction, const Color color)
{
    _reflection = reflection;
    _refraction = refraction;
    _color = color;
}

bool Triangle::rayIntersect(const Ray & ray, Point3D & intersect) const
{
    Point3D A = _A;
    Point3D B = _B;
    Point3D C = _C;
    Point3D n = normal();
    Plane myPlane(*this);
    if (myPlane.rayIntersect(ray, intersect)) {
        if (((B - A) ^ (intersect - A)) * n < 0)
            return false;
        if (((A - C) ^ (intersect - C)) * n < 0)
            return false;
        if (((C - B) ^ (intersect - B)) * n < 0)
            return false;
        return true;
    }
    return false;
}

Point3D Triangle::normal(const Point3D & p) const
{
    Point3D A = Point3D(_A);
    Point3D B = Point3D(_B);
    Point3D C = Point3D(_C);
    Point3D n = (B - A) ^ (C - A);
    return n * (1.0 / n.len());
}

Box Triangle::getBox() const
{
    long double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = min(_A.x(), _B.x(), _C.x());
    xmax = max(_A.x(), _B.x(), _C.x());
    ymin = min(_A.y(), _B.y(), _C.y());
    ymax = max(_A.y(), _B.y(), _C.y());
    zmin = min(_A.z(), _B.z(), _C.z());
    zmax = max(_A.z(), _B.z(), _C.z());
    Box b;
    b.A = Point3D(xmin, ymin, zmin);
    b.B = Point3D(xmax, ymax, zmax);
    return b;
}

