#pragma once
#include <stdio.h>
#include <iostream>
#include <iomanip>

const double EPS = 1E-9;

enum Axis {
    x, y, z
};

class Point3D {
public:
    Point3D() : _x(0), _y(0), _z(0) {};
    Point3D(const double & x, const double & y, const double z) : _x(x), _y(y), _z(z) {};
    Point3D(const Point3D & s) : _x(s.x()), _y(s.y()), _z(s.z()) {};
    
    double x() const;
    double y() const;
    double z() const;
    double coordAxis(Axis axis) const;

    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    double len();

    Point3D operator+(const Point3D & p) const;
    Point3D operator-(const Point3D & p) const;
    //Point3D operator-(Point3D & p);
    Point3D operator^(const Point3D & p);
    double operator*(const Point3D & p);
    Point3D operator*(double k);

    bool operator==(const Point3D & p);
    bool operator!=(const Point3D & p);

    friend std::istream& operator>>(std::istream& is, Point3D& p);

private:
    double _x;
    double _y;
    double _z;
};