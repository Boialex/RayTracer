#include "Scene.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <limits>
#include <sstream>
#include <map>

#include <chrono>

static const double LESSLIGHT = 10.0;

int Scene::pixelsV() const
{
    return nVPixels;
}

int Scene::pixelsH() const
{
    return nHPixels;
}

void Scene::render(const int vpixels, const int hpixels)
{
    t = new KDTree(objects);
    std::cout << objects.size();
    nVPixels = vpixels;
    nHPixels = hpixels;
    pixels.resize(vpixels);
    for (int i = 0; i < vpixels; ++i) {
        pixels[i].resize(hpixels); 
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Point3D dx = (_B - _A) * (1.0 / nVPixels);
    Point3D dy = (_D - _A) * (1.0 / nHPixels);
    std::cout << std::endl;
    for (int i = 0; i < nVPixels; ++i) {
        if (i == nVPixels / 4) {
            end = std::chrono::system_clock::now();
            long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "25% " << time << " ms" << std::endl;
        }
        if (i == nVPixels / 2) {
            end = std::chrono::system_clock::now();
            long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "50% " << time << " ms" << std::endl;
        }
        if (i == 3 * nVPixels / 4) {
            end = std::chrono::system_clock::now();
            long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "75% " << time << " ms" << std::endl;
        }
        for (int j = 0; j < nHPixels; ++j) {
            Ray ray(_eye, Point3D(_A.x() + dx.x() * i + dy.x() * j, 
                                  _A.y() + dx.y() * i + dy.y() * j, 
                                  _A.z() + dx.z() * i + dy.z() * j));
            IntersectionData data(false);
            if (t->intersect(ray, data)) {
                countColor(ray, data.intersection, data.obj, i, j);
            } 
            /*
            int nearest = 0;
            long double nearDist = DBL_MAX;
            bool any = false;
            IntersectionData cur(false);
            for (size_t k = 0; k < objects.size(); ++k) {
                if (objects[k]->rayIntersect(ray, cur)) {
                    any = true;
                    if ((cur.intersection - _eye).len() < nearDist) {
                        nearDist = (cur.intersection - _eye).len();
                        nearest = k;
                    }
                }
            }
            objects[nearest]->rayIntersect(ray, data);
            if (any) {
                countColor(ray, data.intersection, data.obj, i, j);
            }
            */
            //IntersectionData * current = &cur;  
        }
    }

}

void Scene::countColor(Ray & ray, Point3D & intersection, IFigure * obj, int i, int j)
{
    Color color = obj->color();
    color.convertRGBToLab();

    color.red /= LESSLIGHT;
    double minlight = color.red;
    double dif = minlight * (LESSLIGHT - 1);
    
    Point3D beginRay = intersection;
    Point3D n = obj->normal(intersection);

    if (ray.a() * n > 0)
        beginRay = intersection - n * 0.001;
    else
        beginRay = intersection + n * 0.001;

    double add = 0;
    for (auto sun : suns) {
        Ray tolight(beginRay, sun->getPos());
        if ((tolight.a() * n) * (ray.a() * n) > 0)
            continue;
        bool clear = true;
        IntersectionData  l(false);
        if (!t->intersect(tolight, l) || (l.intersection - beginRay).len() > (sun->getPos() - beginRay).len()) {
            long double dist = (sun->getPos() - beginRay).len();
            add += dif * sun->getPower() / norm.power * pow(norm.distance, 2) / pow(dist, 2) * pow(tolight.a() * n, 2);
        }
    }
    color.red = min(color.red + add, 100);

    color.convertLabToRGB();
    pixels[i][j] = color;
}

void Scene::paint()
{
    glBegin(GL_POINTS);
    glPointSize(1.0 / max(nVPixels, nHPixels));
    for (int i = 0; i < nVPixels; ++i) {
        for (int j = 0; j < nHPixels; ++j) {
            Color color = pixels[i][j];
            glColor3f(color.red, color.green, color.blue);
            glVertex2f((1.0 * i / nVPixels), (1.0 * (nHPixels - j) / nHPixels));
        }
    }
    glEnd();
}

Illuminant::Illuminant(const Point3D O, const double power)
{
    _O = O;
    _power = power;
}

Illuminant::Illuminant()
{
    _O = Point3D();
    _power = 0;
}

Point3D Illuminant::getPos() const
{
    return _O;
}

double Illuminant::getPower() const
{
    return _power;
}

