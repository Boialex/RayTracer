#pragma once
#include "Figure.h"

class Box {
public:
    Box();
    Box(const Point3D A, const Point3D B);
    Box(const std::vector<std::shared_ptr<IFigure>> & objs);

    Point3D getA() const;
    Point3D getB() const;

    bool intersect(const Ray ray) const;
    int longestaxis() const;
    double longestlen() const;

private:
    Point3D _A, _B;
};
