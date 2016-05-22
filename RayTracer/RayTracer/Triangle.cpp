#include "Triangle.h"
#include "Plain.h"

Triangle::Triangle(const double reflect, const double refract, const Color color, 
                    const Point3D A, const Point3D B, const Point3D C)
{
    _A = A;
    _B = B;
    _C = C;
    _reflect = reflect;
    _refract = refract;
    _color = color;

    n = (B - A) ^ (C - A);
    n = n * (1.0 / n.len());
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

double Triangle::reflect() const
{
    return _reflect;
}

double Triangle::refract() const
{
    return _refract;
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
    n = (B - A) ^ (C - A);
    n = n * (1.0 / n.len());
}

void Triangle::setParams(const double reflect, const double refract, const Color color)
{
    _reflect = reflect;
    _refract = refract;
    _color = color;
}

bool Triangle::rayIntersect(const Ray & ray, IntersectionData & data) 
{
    Point3D A = _A;
    Point3D B = _B;
    Point3D C = _C;
    Plane myPlane(*this);
    if (myPlane.rayIntersect(ray, data.intersection)) {
        if (((B - A) ^ (data.intersection - A)) * n < 0)
            return false;
        if (((A - C) ^ (data.intersection - C)) * n < 0)
            return false;
        if (((C - B) ^ (data.intersection - B)) * n < 0)
            return false;
        data.obj = this;
        data.intersects = true;
        return true;
    }
    return false;
}

Point3D Triangle::normal(const Point3D & p) const
{
    return n;
}

Box Triangle::getBox() const
{
    double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = min(_A.x(), _B.x(), _C.x());
    xmax = max(_A.x(), _B.x(), _C.x());
    ymin = min(_A.y(), _B.y(), _C.y());
    ymax = max(_A.y(), _B.y(), _C.y());
    zmin = min(_A.z(), _B.z(), _C.z());
    zmax = max(_A.z(), _B.z(), _C.z());
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

