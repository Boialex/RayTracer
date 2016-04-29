#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>

const long double EPS = 1E-9;

class Point3D {
public:
    Point3D() : _x(0), _y(0), _z(0) {};
    Point3D(const long double & x, const long double & y, const long double z) : _x(x), _y(y), _z(z) {};
    Point3D(const Point3D & s) : _x(s.x()), _y(s.y()), _z(s.z()) {};
    
    long double x() const;
    long double y() const;
    long double z() const;

    void setX(long double newX);
    void setY(long double newY);
    void setZ(long double newZ);

    long double len();

    Point3D operator+(const Point3D & p) const;
    Point3D operator-(const Point3D & p) const;
    //Point3D operator-(Point3D & p);
    Point3D operator^(const Point3D & p);
    long double operator*(const Point3D & p);
    Point3D operator*(long double k);

    bool operator==(const Point3D & p);
    bool operator!=(const Point3D & p);

    friend std::istream& operator>>(std::istream& is, Point3D& p);

private:
    long double _x;
    long double _y;
    long double _z;
};