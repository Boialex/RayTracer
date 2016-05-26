#include "Box.h"
#include <algorithm>

KDPlane::KDPlane(const Axis axis, const double coord)
{
    _axis = axis;
    _coord = coord;

    if (_axis == Axis::x) 
        n = Point3D(1, 0, 0);
    else if (_axis == Axis::y) 
        n = Point3D(0, 1, 0);
    else if (_axis == Axis::z) 
        n = Point3D(0, 0, 1);
}

double KDPlane::distance(const Point3D point) const
{
    if (_axis == Axis::x)
        return point.x() - _coord;    
    else if (_axis == Axis::y) 
        return point.y() - _coord;  
    else if (_axis == Axis::z) 
        return point.z() - _coord;
    return 0;
}

bool KDPlane::rayIntersect(const Ray ray, Point3D & intersection) const
{
    double d = distance(ray.r0());
    int k = 0;
    if (d > 0)
        k = 1;
    else if (d < 0)
        k = -1;
    if (ray.a() * n * k >= 0) 
        return false;
    intersection = ray.r0() + ray.a() * fabs(d / (ray.a() * n));
    return true;
}

Point3D KDPlane::normal() const
{
    return n;
}

Axis KDPlane::getAxis() const
{
    return _axis;
}

double KDPlane::getCoord() const
{
    return _coord;
}

void KDPlane::setAxis(const Axis axis)
{
    _axis = axis;
}

void KDPlane::setCoord(const double coord)
{
    _coord = coord;
}             

Point3D Box::getA() const
{
    return _A;
}

Point3D Box::getB() const
{
    return _B;
}

void Box::setA(const Point3D A)
{
    _A = A;
}

void Box::setB(const Point3D B)
{
    _B = B;
}

bool Box::hasPoint(const Point3D p) const
{
    if ((p.x() < _B.x() || isZero(p.x() - _B.x())) && (p.x() > _A.x() || isZero(p.x() - _A.x())) &&
        (p.y() < _B.y() || isZero(p.y() - _B.y())) && (p.y() > _A.y() || isZero(p.y() - _A.y())) &&
        (p.z() < _B.z() || isZero(p.z() - _B.z())) && (p.z() > _A.z() || isZero(p.z() - _A.z())))
        return true;
    return false;
    
}

Axis Box::longestaxis() const
{
    double x = _B.x() - _A.x();
    double y = _B.y() - _A.y();
    double z = _B.z() - _A.z();
    if (x >= y && x >= z)
        return Axis::x;
    if (y >= x && y >= z)
        return Axis::y;
    if (z >= x && z >= y)
        return Axis::z;
    return Axis::x;
}

double Box::longestlen() const
{
    double x = _B.x() - _A.x();
    double y = _B.y() - _A.y();
    double z = _B.z() - _A.z();
    return max(x, y, z);
}

int Box::rayIntersection(const Ray ray, Point3D & first, Point3D & second) const
{
    double tn, tf;
    tn = DBL_MIN;
    tf = DBL_MAX;
    Axis s[3];
    s[0] = Axis::x;
    s[1] = Axis::y;
    s[2] = Axis::z;
    for (int i = 0; i < 3; ++i) {
        Axis axis = s[i];
        double tnear, tfar;
        findParams(_A.coordAxis(axis), _B.coordAxis(axis), ray.r0().coordAxis(axis), ray.a().coordAxis(axis), tnear, tfar);
        tn = max(tn, tnear);
        tf = min(tf, tfar);
    }
    if (tn >= tf || tf < 0.0f) {
        return 0;
    }
    if (tn < 0.0f) {
        first = ray.r0() + ray.a() * tf;
        return 1;
    }
    first = ray.r0() + ray.a() * tn;
    second = ray.r0() + ray.a() * tf;
    return 2;
}

void Box::findParams(const double left, const double right, const double point, const double a, double & t1, double & t2) const
{
    if (a == 0) {
        if (left <= point && right >= point) {
            t1 = DBL_MIN;
            t2 = DBL_MAX;
        } else {
            t1 = 1;
            t2 = -1;
        }
    } else {
        t1 = (left - point) / a;
        t2 = (right - point) / a;
        if (t1 > t2) {
            std::swap(t1, t2);
        }
    }
}

