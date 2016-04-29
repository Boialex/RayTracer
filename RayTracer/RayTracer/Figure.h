#pragma once
#include "Ray.h"
#include "Color.h"
#include <stdarg.h>
#include <vector>
#include <memory>

template <typename... Args>
long double min(long double a, Args ... args);

template <typename... Args>
long double max(long double a, Args ... args);

class Box;

class IFigure {
public:
    virtual bool rayIntersect(const Ray & ray, Point3D & intersect) const = 0;
    virtual Point3D normal(const Point3D & p) const = 0;
    virtual Color color() const = 0;
    virtual Box getBox() const = 0;
    
    virtual ~IFigure() {};
};

#include "Box.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Parallelogramm.h"
#include "Quadrangle.h"

enum figure_type {
    ht_triangle,
    ht_sphere,
    ht_parallelogramm,
    ht_quadrangle
};

IFigure * createFigure(figure_type type, const long double reflection, const long double refraction,
                        const Color color, const Point3D first, ...);