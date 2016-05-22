#pragma once
#include "Figure.h"

class KDPlane {
public:
    KDPlane() : _axis(Axis::x), _coord(0) {}
    KDPlane(const Axis axis, const double coord);
    
    double distance(const Point3D point) const;
    bool rayIntersect(const Ray ray, Point3D & intersection) const;
    Point3D normal() const;
    
    Axis getAxis() const;
    double getCoord() const;
    
    void setAxis(const Axis axis);
    void setCoord(const double coord);
    
private:
    Axis _axis;
    double _coord;

    Point3D n;
};

class Box {
public:
    Box() : _A(Point3D()), _B(Point3D()) {};
    Box(const Point3D  A, const Point3D B) : _A(A), _B(B) {};
    
    int rayIntersection(const Ray ray, Point3D & first, Point3D & second) const;
    bool hasPoint(const Point3D p) const;
    Axis longestaxis() const;
    double longestlen() const;

    Point3D getA() const;
    Point3D getB() const;

    void setA(const Point3D A);
    void setB(const Point3D B);
    
private:
    void findParams(const double left, const double right, const double point, const double a, double & t1, double & t2) const;

    Point3D _A, _B;
};