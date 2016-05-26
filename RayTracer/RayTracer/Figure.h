#pragma once
#include "HelpFunc.h"
#include "Ray.h"
#include "Color.h"
#include <stdarg.h>
#include <vector>
#include <memory>

class Box;

struct IntersectionData;

class IFigure {
public:
    virtual bool rayIntersect(const Ray & ray, IntersectionData & data) = 0;
    virtual Point3D normal(const Point3D & p) const = 0;
    virtual Color color() const = 0;
    virtual Box getBox() const = 0;
    virtual void setParams(const double reflect, const double refracr, const Color color) = 0;
    virtual double reflect() const = 0;
    virtual double refract() const = 0;
    virtual ~IFigure() {};
};

struct IntersectionData {
public:
    IntersectionData(bool intersects) : intersects(intersects) {}
    //IntersectionData(bool intersects, Color color, Point collisionPoint, Point collisionNormal,
    //    IMaterial* material, Point photonDirection, float reflectionDepth = 0, float refractionDepth = 0);
    bool intersects;
    IFigure * obj;
    //IFigure * owner;
    Point3D intersection;
    //Color PixelColor;
    //Point3D IntersectionPoint;
    //Point3D IntersectionNormal;
    //IFigure* Owner;
    //IMaterial* Material;
    //Point3D PhotonDirection;
    //float ReflectionDepth;
    //float RefractionDepth;
};


#include "Box.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Quadrangle.h"

enum figure_type {
    ht_triangle,
    ht_sphere,
    ht_quadrangle
};

IFigure * createFigure(figure_type type, const double reflect, const double refract,
                        const Color color, const Point3D first, ...);