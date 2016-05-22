#pragma once
#include "Figure.h"
#include "Point3D.h"

class Triangle : public IFigure {
public:
    Triangle() : _A(), _B(), _C(), _color(0, 0, 0) {};
    Triangle(const double reflect, const double refract, const Color color,
              const Point3D A, const Point3D B, const Point3D C);
    
    Point3D A() const;
    Point3D B() const;
    Point3D C() const;
    double reflect() const;
    double refract() const;
    Color color() const;

    void setA(const Point3D A);
    void setB(const Point3D B);
    void setC(const Point3D C);
    void setPoints(const Point3D A, const Point3D B, const Point3D C);
    void setParams(const double reflect, const double refract, const Color color);
    
    bool rayIntersect(const Ray & ray, IntersectionData & data);
    Point3D normal(const Point3D & p = Point3D()) const;
    Box getBox() const;

private:
    Point3D _A, _B, _C;
    double _reflect;
    double _refract;
    Color _color;

    Point3D n;
};