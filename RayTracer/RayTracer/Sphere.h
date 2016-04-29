#pragma once
#include "Figure.h"

class Sphere : public IFigure {
public:
    Sphere() {};
    Sphere(const long double reflection, const long double refraction, const Color color, const Point3D O, const long double r);

    long double r() const;
    Point3D O() const;
    long double reflection() const;
    long double refraction() const;
    Color color() const;

    void setRadius(const long double r);
    void setCenter(const Point3D O);
    void setParams(const long double reflection, const long double refraction, const Color color);

    Point3D normal(const Point3D & p = Point3D()) const;
    bool rayIntersect(const Ray & ray, Point3D & intersect) const;
    Box getBox() const;

private:
    long double _reflection;
    long double _refraction;
    Color _color;
    long double _r;
    Point3D _O;
};
