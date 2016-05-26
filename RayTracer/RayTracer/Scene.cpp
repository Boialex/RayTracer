#include "Scene.h"
#include <fstream>
#include <Windows.h>
#include <string>
#include <limits>
#include <sstream>
#include <map>

#include <chrono>

static const int ANTIALIASING = 1;
static const double LESSLIGHT = 10.0;
static const int DEPTH = 5;
static const bool REFRACT = true;
static const bool REFLECT = true;

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
    std::cout << "number of polygons: " << objects.size() << std::endl;
    nVPixels = vpixels * ANTIALIASING;
    nHPixels = hpixels * ANTIALIASING;
    pixels.resize(nVPixels);
    for (int i = 0; i < nVPixels; ++i) {
        pixels[i].resize(nHPixels); 
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    Point3D dx = (_B - _A) * (1.0 / nVPixels);
    Point3D dy = (_D - _A) * (1.0 / nHPixels);
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
                pixels[i][j] = countColor(ray, data.intersection, data.obj, 0);
            }  
        }
    }

    end = std::chrono::system_clock::now();
    long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "100% " << time << " ms" << std::endl;
}

Color Scene::countLight(Ray & ray, Point3D & intersection, IFigure * obj)
{
    Point3D beginRay = intersection;
    Point3D n = obj->normal(intersection);
    if (ray.a() * n > 0)
        beginRay = intersection - n * EPS;
    else
        beginRay = intersection + n * EPS;

    Color color = obj->color(); 
    color.convertRGBToLab();

    color.red /= LESSLIGHT;
    double minlight = color.red;
    double dif = minlight * (LESSLIGHT - 1);

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
    color.red += add;
    color.cut();
    color.convertLabToRGB();
    return color;
}

Color Scene::countColor(Ray & ray, Point3D & intersection, IFigure * obj, int depth)
{
    Color color = Color();
    if (depth > DEPTH)
        return color;
    bool innerReflection = false;
    double alpha = obj->reflect();
    double gamma = obj->refract();
    Point3D n = obj->normal(intersection);
    Point3D beginRay = intersection;
    if (REFRACT && gamma > EPS) {
        if (ray.a() * n > 0)
            beginRay = intersection + n * EPS;
        else {
            beginRay = intersection - n * EPS;
            gamma = 1.0 / gamma;
        }
        Point3D alongproj = n * (ray.a() * n);
        Point3D transproj = ray.a() - alongproj;
        double angle = asin(transproj.len()) * gamma;
        if (fabs(angle) >= 1) {
            innerReflection = true;
        } else {
            angle = asin(angle);
            transproj = transproj * (alongproj.len() / transproj.len() * tan(angle));
            Ray refractRay(beginRay, beginRay + alongproj + transproj);
            IntersectionData refr(false);
            if (t->intersect(refractRay, refr))
                return countColor(refractRay, refr.intersection, refr.obj, depth + 1);
            return Color();
        }
    }
    if (innerReflection)
        alpha = 1;
    if (REFLECT && alpha > EPS) {
        color = countLight(ray, intersection, obj);
        
        if (ray.a() * n > 0)
            beginRay = intersection - n * EPS;
        else
            beginRay = intersection + n * EPS;
        
        color *= (1 - alpha);
        Point3D n = obj->normal(intersection);
        double proj = ray.a() * n;
        Point3D dir = n * (-2.0 * proj) + ray.a();
        IntersectionData refl(false);
        Ray mir(beginRay, beginRay + dir * 10);
        if (t->intersect(mir, refl)) {
            Color Y = countColor(mir, refl.intersection, refl.obj, depth + 1);
            Y *= alpha;
            color += Y;
        }
        return color;
    }
    return countLight(ray, intersection, obj);
}

void Scene::paint()
{
    glBegin(GL_POINTS);
    glPointSize(1.0 / max(nVPixels, nHPixels));
    for (int i = 0; i < nVPixels; i += ANTIALIASING) {
        for (int j = 0; j < nHPixels; j += ANTIALIASING) {
            Color color;
            for (int u = 0; u < ANTIALIASING; ++u)
                for (int v = 0; v < ANTIALIASING; ++v) {
                    color += pixels[i + u][j + v];
                }
            int n = ANTIALIASING * ANTIALIASING;
            color /= n;
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
