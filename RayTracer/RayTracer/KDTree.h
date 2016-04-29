#pragma once
#include "Figure.h"
#include <vector>
#include <memory>

static const double emptycost = 0;

class KDTree {
public:
    KDTree(const std::vector<std::shared_ptr<IFigure>> & newobj);
    bool hit(const Ray & ray, Point3D & intersection);

private:
    struct KDNode {
        KDNode();
        long double findBorder(int axis, double & sah) const;
        double distleft(int axis, long double border) const;
        double distright(int axis, long double border) const;
        void build();
        bool hit(const Ray & ray, Point3D & intersection);
        
        double _border;
        Box box;
        std::unique_ptr<KDNode> left;
        std::unique_ptr<KDNode> right;
        std::vector<std::shared_ptr<IFigure>> obj;
        //KDNode * build(const std::vector<std::shared_ptr<IFigure>> & newobj, const int depth);
    };
    
    std::unique_ptr<KDNode> head;
};