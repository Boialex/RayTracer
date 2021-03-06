#include "Point3D.h"

double Point3D::x() const
{
    return _x;
}

double Point3D::y() const
{
    return _y;
}

double Point3D::z() const
{
    return _z;
}

double Point3D::coordAxis(Axis axis) const
{
    if (axis == 0)
        return _x;
    if (axis == 1)
        return _y;
    if (axis == 2)
        return _z;
}

void Point3D::setX(double newX)
{
    _x = newX;
}

void Point3D::setY(double newY)
{
    _y = newY;
}

void Point3D::setZ(double newZ)
{
    _z = newZ;
}

double Point3D::len()
{
    return sqrt(_x * _x + _y * _y + _z * _z);
}

Point3D Point3D::operator+(const Point3D & p) const
{
    return Point3D(_x + p.x(), _y + p.y(), _z + p.z());
}

Point3D Point3D::operator-(const Point3D & p) const
{
    return Point3D(_x - p.x(), _y - p.y(), _z - p.z());
}

Point3D Point3D::operator^(const Point3D & p)
{
    return Point3D(_y * p.z() - _z * p.y(),
        -_x * p.z() + _z * p.x(),
        _x * p.y() - _y * p.x());
}

double Point3D::operator*(const Point3D & p)
{
    return _x * p.x() + _y * p.y() + _z * p.z();
}

Point3D Point3D::operator*(double k)
{
    return Point3D(k * _x, k * _y, k * _z);
}

bool Point3D::operator==(const Point3D & p)
{
    return (fabs(_x - p.x()) <= EPS) && (fabs(_y - p.y()) <= EPS) && (fabs(_z - p.z()) <= EPS);
}

bool Point3D::operator!=(const Point3D & p)
{
    return !((*this) == p);
}

std::istream& operator>>(std::istream& is, Point3D& p)
{
    double x, y, z;
    is >> x >> y >> z;
    p.setX(x);
    p.setY(y);
    p.setZ(z);
    return is;
}