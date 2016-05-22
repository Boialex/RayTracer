#pragma once
#include "Figure.h"

class Sphere : public IFigure {
public:
    Sphere() {};
    Sphere(const double reflect, const double refract, const Color color, const Point3D O, const double r);

    double r() const;
    Point3D O() const;
    double reflect() const;
    double refract() const;
    Color color() const;

    void setRadius(const double r);
    void setCenter(const Point3D O);
    void setParams(const double reflect, const double refract, const Color color);

    Point3D normal(const Point3D & p = Point3D()) const;
    bool rayIntersect(const Ray & ray, IntersectionData & data);
    Box getBox() const;

private:
    double _reflect;
    double _refract;
    Color _color;
    double _r;
    Point3D _O;
};
