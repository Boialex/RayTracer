#pragma once
#include "Scene.h"
#include <map>
#include <fstream>
#include <string>
#include <sstream>

class Reader {
public:
    Reader(const std::string & s);
    ~Reader();

    friend class Scene;

    void read(Scene& scene);

private:
    void readViewport(Scene & scene);

    void readMaterials();
    void readEntry();

    void readLights(Scene & scene);
    void readReference(Scene & scene);
    void readPoint(Scene & scene);

    void readGeometry(Scene & scene);
    void readSphere(Scene & scene);
    void readTriangle(Scene & scene);
    void readQuadrangle(Scene & scene);

    std::ifstream input;
    std::stringstream ss;
    std::string s;
    std::string buffer1, buffer2, buffer3;
    std::map<std::string, Scene::Params> materials;
    double x[4], y[4], z[4];
};
