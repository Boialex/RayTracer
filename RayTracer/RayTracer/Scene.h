#pragma once

#include "Figure.h"
#include <vector>
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <glut.h>  
#include <memory>

class Illuminant {
public:
    Illuminant(const Point3D O, const double intensity);

    Point3D getPos() const;

private:
    Point3D _O;
    double _intensity;
};

class Scene {
public:
    Scene() {};

    int pixelsV() const;
    int pixelsH() const;

    void input();
    void paint();

private:
    std::vector<std::shared_ptr<IFigure>> objects;
    std::vector<std::shared_ptr<Illuminant>> suns;
    Point3D _eye;
    Point3D _A, _B, _C, _D;
    int nVPixels;
    int nHPixels;
    double lightConst;
};
