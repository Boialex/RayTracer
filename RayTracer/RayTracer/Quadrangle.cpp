#include "Quadrangle.h"
#include "Plain.h"

Quadrangle::Quadrangle(const double reflect, const double refract, const Color color,
    const Point3D A, const Point3D B, const Point3D C, const Point3D D)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _reflect = reflect;
    _refract = refract;
    _color = color;


    n = (_B - _A) ^ (_C - _A);
    n = n * (1.0 / n.len());
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

double Quadrangle::reflect() const
{
    return _reflect;
}

double Quadrangle::refract() const
{
    return _refract;
}

Color Quadrangle::color() const
{
    return _color;
}

void Quadrangle::setA(const Point3D A)
{
    _A = A;
    n = (_B - _A) ^ (_C - _A);
    n = n * (1.0 / n.len());
}

void Quadrangle::setB(const Point3D B)
{
    _B = B;
    n = (_B - _A) ^ (_C - _A);
    n = n * (1.0 / n.len());
}

void Quadrangle::setC(const Point3D C)
{
    _C = C;
    n = (_B - _A) ^ (_C - _A);
    n = n * (1.0 / n.len());
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
    n = (B - A) ^ (C - A);
    n = n * (1.0 / n.len());
}

void Quadrangle::setParams(const double reflect, const double refract, const Color color)
{
    _reflect = reflect;
    _refract = refract;
    _color = color;
}

bool Quadrangle::rayIntersect(const Ray & ray, IntersectionData & data) 
{
    Point3D A = _A;
    Point3D B = _B;
    Point3D C = _C;
    Point3D D = _D;
    Plane myPlane(*this);
    if (myPlane.rayIntersect(ray, data.intersection)) {
        if (((B - A) ^ (data.intersection - A)) * n < 0)
            return false;
        if (((A - D) ^ (data.intersection - D)) * n < 0)
            return false;
        if (((C - B) ^ (data.intersection - B)) * n < 0)
            return false;
        if (((D - C) ^ (data.intersection - C)) * n < 0)
            return false;
        data.obj = (this);
        data.intersects = true;
        return true;
    }
    return false;
}

Point3D Quadrangle::normal(const Point3D & p) const
{
    return n;
}

Box Quadrangle::getBox() const
{
    double xmin, xmax, ymin, ymax, zmin, zmax;
    xmin = min(_A.x(), _B.x(), _C.x(), _D.x());
    xmax = max(_A.x(), _B.x(), _C.x(), _D.x());
    ymin = min(_A.y(), _B.y(), _C.y(), _D.y());
    ymax = max(_A.y(), _B.y(), _C.y(), _D.y());
    zmin = min(_A.z(), _B.z(), _C.z(), _D.z());
    zmax = max(_A.z(), _B.z(), _C.z(), _D.z());
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


