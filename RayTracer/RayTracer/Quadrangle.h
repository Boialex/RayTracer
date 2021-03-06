#pragma once
#include "Figure.h"
#include "Point3D.h"

class Quadrangle : public IFigure {
public:
    Quadrangle() : _A(), _B(), _C(), _D(), _color(0, 0, 0) {};
    Quadrangle(const double reflect, const double refract, const Color color,
        const Point3D A, const Point3D B, const Point3D C, const Point3D D);

    Point3D A() const;
    Point3D B() const;
    Point3D C() const;
    Point3D D() const;
    double reflect() const;
    double refract() const;
    Color color() const;

    void setA(const Point3D A);
    void setB(const Point3D B);
    void setC(const Point3D C);
    void setD(const Point3D D);

    void setPoints(const Point3D A, const Point3D B, const Point3D C, const Point3D D);
    void setParams(const double reflect, const double refract, const Color color);

    bool rayIntersect(const Ray & ray, IntersectionData & data);
    Point3D normal(const Point3D & p = Point3D()) const;
    Box getBox() const;

private:
    Point3D _A, _B, _C, _D;
    double _reflect;
    double _refract;
    Color _color;

    Point3D n;
};
