#pragma once
#include "Figure.h"
#include "KDTree.h"
#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>  
#include <memory>

class Illuminant {
public:
    Illuminant(const Point3D O, const double power);
    Illuminant();

    Point3D getPos() const;
    double getPower() const;

private:
    Point3D _O;
    double _power;
};

class Scene {
public:
    int pixelsV() const;
    int pixelsH() const;

    void render(const int vpixels, const int hpixels);
    void paint();
    
    friend class Reader;

private:
    Color countColor(Ray & raty, Point3D & intersection, IFigure * obj, int depth);

    struct Params {
        double reflect;
        double refract;
        Color color;
    };

    struct light {
        double power;
        double distance;
    };

    std::vector<IFigure*> objects;
    std::vector<Illuminant*> suns;

    std::vector<std::vector<Color>> pixels;

    Point3D _eye;
    Point3D _A, _B, _C, _D;
    int nVPixels;
    int nHPixels;
    light norm;

    KDTree * t;
};

#include "Reader.h"
