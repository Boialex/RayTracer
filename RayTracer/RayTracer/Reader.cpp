#include "Reader.h"
#include <chrono>

Reader::Reader(const std::string & s)
{
    input.open(s);
}

Reader::~Reader() 
{
    input.close();
}

void Reader::read(Scene & scene)
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();

    std::map<std::string, Scene::Params> materials;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "viewport") {
            readViewport(scene);
        }
        else if (s == "materials") {
            readMaterials();
        }
        else if (s == "lights") {
            readLights(scene);
        }
        else if (s == "geometry") {
            readGeometry(scene);
        }
    }
    end = std::chrono::system_clock::now();
    long long time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "read time = " << time << " ms" << std::endl;

    materials.clear();
}

void Reader::readViewport(Scene & scene)
{
    double xO, yO, zO;
    double xtl, ytl, ztl;
    double xtr, ytr, ztr;
    double xdl, ydl, zdl;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "topleft") {
            ss >> xtl >> ytl >> ztl;
        }
        else if (s == "topright") {
            ss >> xtr >> ytr >> ztr;
        }
        else if (s == "bottomleft") {
            ss >> xdl >> ydl >> zdl;
        }
        else if (s == "origin") {
            ss >> xO >> yO >> zO;            
        }
        else if (s == "endviewport") {
            scene._eye = Point3D(xO, yO, zO);
            scene._A = Point3D(xtl, ytl, ztl);
            scene._B = Point3D(xtr, ytr, ztr);
            scene._D = Point3D(xdl, ydl, zdl);
            scene._C = scene._D + (scene._B - scene._A);
            return;
        }
    }
}

void Reader::readMaterials()
{
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        else if (s == "entry") {
            readEntry();
        }
        else if (s == "endmaterials") {
            return;
        }
    }
}

void Reader::readEntry()
{
    Scene::Params cur;
    cur.reflect = cur.refract = 0;
    cur.color = Color();
    std::string name;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "name") {
            ss >> name;
        }
        else if (s == "color") {
            int x, y, z;
            ss >> buffer1 >> buffer2 >> buffer3;
            x = std::stoi(buffer1);
            y = std::stoi(buffer2);
            z = std::stoi(buffer3);
            cur.color = Color(x, y, z);
        }
        else if (s == "reflect") {
            ss >> cur.reflect;
        }
        else if (s == "refract") {
            ss >> cur.refract;
        }
        else if (s == "endentry") {
            materials.insert(std::pair<std::string, Scene::Params>(name, cur));
            return;
        }
    }
}

void Reader::readLights(Scene & scene)
{
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "point") {
            readPoint(scene);
        }
        if (s == "reference") {
            readReference(scene);
        }
        else if (s == "point") {
            readPoint(scene);
        }
        else if (s == "endlights") {
            return;
        }
    }
}

void Reader::readReference(Scene & scene)
{
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "power") {
            ss >> scene.norm.power;            
        }
        else if (s == "distance") {
            ss >> scene.norm.distance;           
        }
        else if (s == "endreference") {
            return;
        }
    }
}

void Reader::readPoint(Scene & scene)
{
    double xO, yO, zO;
    double power;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "coords") {
            ss >> xO >> yO >> zO;
        }
        else if (s == "power") {
            ss >> power;            
        }
        else if (s == "endpoint") {
            scene.suns.push_back(new Illuminant(Point3D(xO, yO, zO), power));
            return;
        }
    }
}

void Reader::readGeometry(Scene & scene)
{
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        else if (s == "triangle") {
            readTriangle(scene);            
        }
        else if (s == "sphere") {
            readSphere(scene);            
        }
        else if (s == "quadrangle") {
            readQuadrangle(scene);            
        }
        else if (s == "endgeometry") {
            return;
        }
    }
}

void Reader::readSphere(Scene & scene)
{
    Scene::Params cur;
    double x, y, z, r;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "material") {
            ss >> s;
            cur = materials.at(s);            
        }
        else if (s == "coords") {
            ss >> buffer1 >> buffer2 >> buffer3;
            x = std::stod(buffer1);
            y = std::stod(buffer2);
            z = std::stod(buffer3);            
        }
        else if (s == "radius") {
            ss >> buffer1;
            r = std::stod(buffer1);            
        }
        else if (s == "endsphere") {
            scene.objects.push_back(new Sphere(cur.reflect, cur.refract, cur.color, Point3D(x, y, z), r));
            return;
        }
    }
}

void Reader::readTriangle(Scene & scene)
{
    Scene::Params cur;
    int i = 0;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "material") {
            ss >> s;
            cur = materials.at(s);            
        }
        else if (s == "vertex") {
            ss >> buffer1 >> buffer2 >> buffer3;
            x[i] = std::stod(buffer1);
            y[i] = std::stod(buffer2);
            z[i] = std::stod(buffer3);
            ++i;            
        }
        else if (s == "endtriangle") {
            scene.objects.push_back(new Triangle(cur.reflect, cur.refract, cur.color, Point3D(x[0], y[0], z[0]),
                                                                                      Point3D(x[1], y[1], z[1]), 
                                                                                      Point3D(x[2], y[2], z[2])));
            return;
        }
    }
}

void Reader::readQuadrangle(Scene & scene)
{
    Scene::Params cur;
    int i = 0;
    while (getline(input, s)) {
        ss.clear();
        ss.str(s);
        ss >> s;
        if (s[0] == '#') {
            continue;
        }
        if (s == "material") {
            ss >> s;
            cur = materials.at(s);            
        }
        else if (s == "vertex") {
            ss >> buffer1 >> buffer2 >> buffer3;
            x[i] = std::stod(buffer1);
            y[i] = std::stod(buffer2);
            z[i] = std::stod(buffer3);
            ++i;            
        }
        else if (s == "endquadrangle") {
            scene.objects.push_back(new Quadrangle(cur.reflect, cur.refract, cur.color, Point3D(x[0], y[0], z[0]),
                                                                                        Point3D(x[1], y[1], z[1]), 
                                                                                        Point3D(x[2], y[2], z[2]), 
                                                                                        Point3D(x[3], y[3], z[3])));           
            return;
        }
    }
}
