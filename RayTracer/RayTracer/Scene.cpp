#include "Scene.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <limits>

int Scene::pixelsV() const
{
    return nVPixels;
}

int Scene::pixelsH() const
{
    return nHPixels;
}

void Scene::input()
{
    lightConst = 1.1;
    std::fstream in;
    in.open("input.txt");
    in >> _eye;
    in >> _A >> _B >> _C >> _D;
    in >> nVPixels >> nHPixels;
    int nObjects;
    in >> nObjects;
    int reflection, refraction;
    long double r;
    Color color;
    Point3D A, B, C, D;
    Point3D borderA;
    Point3D borderB;
    std::string type;
    //for (int i = 0; i < nObjects; ++i) {
    while (in >> type) {
        switch (type[0]) 
        {
            case 't':
                in >> reflection >> refraction >> color;
                in >> A >> B >> C;
                objects.push_back(std::shared_ptr<IFigure>(createFigure(ht_triangle, 
                                                reflection, refraction, color, A, 
                                                B.x(), B.y(), B.z(), 
                                                C.x(), C.y(), C.z())));
                break;
            case 's':
                in >> reflection >> refraction >> color;
                in >> r >> A;
                objects.push_back(std::shared_ptr<IFigure>(createFigure(ht_sphere, reflection, refraction, color, A, r)));
                break;
            case 'r':
                in >> reflection >> refraction >> color;
                in >> A >> B >> C >> D;
                objects.push_back(std::shared_ptr<IFigure>(createFigure(ht_quadrangle, 
                                                reflection, refraction, color, A,
                                                B.x(), B.y(), B.z(),
                                                C.x(), C.y(), C.z(),
                                                D.x(), D.y(), D.z())));
                break;
            case 'p':
                in >> reflection >> refraction >> color;
                in >> A >> B >> C >> D;
                objects.push_back(std::shared_ptr<IFigure>(createFigure(ht_parallelogramm, 
                                                reflection, refraction, color, A,
                                                B.x(), B.y(), B.z(),
                                                C.x(), C.y(), C.z(),
                                                D.x(), D.y(), D.z())));
                break;
            default:
                continue;
        } 
    }
    Point3D pos(10, -2, 15);
    suns.push_back(std::shared_ptr<Illuminant>(new Illuminant(pos, 1.0)));
}

void Scene::paint()
{
    Point3D dx = (_B - _A) * (1.0 / nVPixels);
    Point3D dy = (_D - _A) * (1.0 / nHPixels);
    Point3D intersect;

    glBegin(GL_POINTS);
    glPointSize(1.0 / max(nVPixels, nHPixels));
    for (int i = 0; i < nVPixels; ++i) {
        for (int j = 0; j < nHPixels; ++j) {
            Ray ray(_eye, Point3D(_A.x() + dx.x() * i + dy.x() * j, 
                                  _A.y() + dx.y() * i + dy.y() * j, 
                                  _A.z() + dx.z() * i + dy.z() * j));
            int nearest = 0;
            long double nearDist = DBL_MAX;
            bool any = false;
            for (int k = 0; k < objects.size(); ++k) {
                if (objects[k]->rayIntersect(ray, intersect)) {
                    any = true;
                    if ((intersect - _eye).len() < nearDist) {
                        nearDist = (intersect - _eye).len();
                        nearest = k;
                    }
                }
            }
            if (any) {
                objects[nearest]->rayIntersect(ray, intersect);
                Color color = objects[nearest]->color();
                color.convertRGBToLab();
                color.red = 0.1;
                color.convertLabToRGB();
                for (int v = 0; v < suns.size(); ++v) {
                    Point3D beginRay;
                    Point3D n = objects[nearest]->normal(Point3D());
                    if (ray.a() * n > 0)
                        beginRay = intersect - n * 0.1;
                    else
                        beginRay = intersect + n * 0.1;
                    Ray tolight(beginRay, suns[v]->getPos());
                    bool clear = true;
                    for (int w = 0; w < objects.size(); ++w)
                        if (objects[w]->rayIntersect(tolight, Point3D())) {
                            clear = false;
                            break;
                        }

                    color.convertRGBToLab();
                    if (clear) {
                        //std::cout << k << std::endl;
                        long double dist = (suns[v]->getPos() - beginRay).len();
                        double dif = 80.0 - color.red;
                        color.red += dif * 100 * lightConst / pow(dist, 2)* pow(tolight.a() * n, 2);
                    }
                    color.convertLabToRGB();
                }

                glColor3f(color.red, color.green, color.blue);
                glVertex2f(double(i) / nVPixels, double(j) / nHPixels);
            }
        }
    }
    glEnd();
}

Illuminant::Illuminant(const Point3D O, const double intensity)
{
    _O = O;
    _intensity = intensity;
}

Point3D Illuminant::getPos() const
{
    return _O;
}
