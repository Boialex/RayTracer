#pragma once
#include "Figure.h"
#include <vector>
#include <memory>

static const int MAXDEPTH = 15;

struct ObjWithBox {
    ObjWithBox(IFigure * obj, const Box * b) : object(obj), box(b) {}
    IFigure* object;
    const Box * box;
};

struct structForSort {
    structForSort(const double newcoord, const ObjWithBox * b) : coord(newcoord), object(b) {}
    double coord;
    const ObjWithBox * object;
    bool operator < (const structForSort & a) const;
};

struct Node {
    void build(const std::vector<structForSort>::iterator & begin, const std::vector<structForSort>::iterator & end);
    bool intersect(const Ray ray, IntersectionData & data) const;
    bool intersectHere(const Ray ray, IntersectionData & data) const;

    Node() : left(NULL), right(NULL) {}
    void split(int h);

    std::vector<ObjWithBox> objectsWithBox;
    Box boundingBox;
    KDPlane splittingPlane;
    Node * left;
    Node * right;
};

class KDTree {
public:
    KDTree(const std::vector<IFigure*> & objects);
    bool intersect(const Ray ray, IntersectionData & data) const;

private:
    Node * root;
    const std::vector<IFigure*> & objects;
    std::vector<Box> boxes;
};