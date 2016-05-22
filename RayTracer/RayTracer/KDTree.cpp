#include "KDTree.h"
#include <algorithm>
 
bool structForSort::operator <(const structForSort & a) const
{
    return coord < a.coord;
}

KDTree::KDTree(const std::vector<IFigure*> & _objects) :objects(_objects), boxes()
{
    if (_objects.size() == 0)
        return;
    boxes.reserve(_objects.size());

    for (auto obj : objects) {
        boxes.push_back(obj->getBox());
    }
    
    double xmin = boxes[0].getA().x();
    double xmax = boxes[0].getB().x();
    double ymin = boxes[0].getA().y();
    double ymax = boxes[0].getB().y();
    double zmin = boxes[0].getA().z();
    double zmax = boxes[0].getB().z();
    for (auto i : boxes) {
        xmin = min(xmin, i.getA().x());
        xmax = max(xmax, i.getB().x());
        ymin = min(ymin, i.getA().y());
        ymax = max(ymax, i.getB().y());
        zmin = min(zmin, i.getA().z());
        zmax = max(zmax, i.getB().z());
    }
    root = new Node();
    root->boundingBox = Box(Point3D(xmin, ymin, zmin), Point3D(xmax, ymax, zmax));
    root->objectsWithBox.reserve(boxes.size());
    for (int i = 0; i < boxes.size(); ++i) {
        root->objectsWithBox.push_back(ObjWithBox((objects[i]), &(boxes[i])));
    }
    root->split(0);
}

void Node::split(int h)
{
    if (h > MAXDEPTH) {
        return;
    }
    Axis axis = boundingBox.longestaxis();
    double max = boundingBox.getB().coordAxis(axis);
    double min = boundingBox.getA().coordAxis(axis);
    std::vector<structForSort> leftBorder, rightBorder;
    leftBorder.reserve(objectsWithBox.size());
    rightBorder.reserve(objectsWithBox.size());
    for (int i = 0; i < objectsWithBox.size(); ++i) {
        leftBorder.push_back(structForSort(objectsWithBox[i].box->getA().coordAxis(axis), &(objectsWithBox[i])));
        rightBorder.push_back(structForSort(objectsWithBox[i].box->getB().coordAxis(axis), &(objectsWithBox[i])));
    }
    std::sort(leftBorder.begin(), leftBorder.end());
    std::sort(rightBorder.begin(), rightBorder.end());
    
    int p, q, n;
    p = 0;
    q = -1;
    n = objectsWithBox.size();
    double coord = min;
    int toleft;
    int toright;
    int bestLeft = toleft = 0;
    int bestRight = toright = n;
    bool previousLeft = true;
    double sah = n * (max - min);
    double bestCoord = min, bestSah = sah;
    while (p < n - 1 || q < n - 1) {
        if (previousLeft == true) {
            ++toleft;
            previousLeft = false;
        }
        if (p >= n - 1) {
            ++q;
            coord = rightBorder[q].coord;
            --toright;
            previousLeft = false;
        }
        else 
            if (q >= n - 1) {
                ++p;
                coord = leftBorder[p].coord;
                previousLeft = true;
            } else {
                if (rightBorder[q + 1].coord < leftBorder[p + 1].coord) {
                    ++q;
                    coord = rightBorder[q].coord;
                    --toright;
                    previousLeft = false;
                }
                else {
                    ++p;
                    coord = leftBorder[p].coord;
                    previousLeft = true;
                }
            }
        double splitSah = toright * (max - coord) + toleft * (coord - min);
        if (splitSah < bestSah) {
            bestSah = splitSah;
            bestCoord = coord;
            bestLeft = toleft;
            bestRight = toright;
        }
    }
    if (bestSah >= (n - 3) * (max - min) || bestCoord == max || bestCoord == min) {
        return;
    }
    coord = bestCoord;
    splittingPlane = KDPlane(axis, coord);
    toleft = 0;
    while (toleft < n - 1 && leftBorder[toleft + 1].coord < bestCoord)
        ++toleft;
    toright = 0;
    while (toright < n - 1 && bestCoord < rightBorder[n - toright - 1].coord)
        ++toright;
    
    left = new Node();
    left->build(leftBorder.begin(), leftBorder.begin() + (toleft + 1));
    Point3D splitNormal = splittingPlane.normal();

    splitNormal = splitNormal * (max - coord);
    left->boundingBox = Box(boundingBox.getA(), boundingBox.getB() - splitNormal);
    
    right = new Node();
    right->build(rightBorder.end() - (toright + 1), rightBorder.end());

    splitNormal = splitNormal * ((coord - min) / (max - coord));
    right->boundingBox = Box(boundingBox.getA() + splitNormal, boundingBox.getB());

    objectsWithBox.clear();
    left->split(h + 1);
    right->split(h + 1);
}

void Node::build(const std::vector<structForSort>::iterator& begin, const std::vector<structForSort>::iterator& end)
{
    objectsWithBox.reserve(end - begin);
    for (auto i = begin; i < end; ++i) {
        objectsWithBox.push_back(*(i->object));
    }
}

bool KDTree::intersect(const Ray ray, IntersectionData & data)const
{
    return root->intersect(ray, data);
}

bool Node::intersect(const Ray ray, IntersectionData & data)const
{
    if (left == NULL || right == NULL) {
        if (objectsWithBox.size() > 0) {
            return intersectHere(ray, data);
        } else {
            return false;
        }
    }
    Point3D first, second;
    int dots = boundingBox.rayIntersection(ray, first, second);
    if (dots == 0) 
        return false;
    if (dots == 1) {
        second = first;
        first = ray.r0();
    }
    bool leftVisited = false, rightVisited = false;
    if (splittingPlane.distance(first) <= 0) {
        leftVisited = true;
        if (left->intersect(ray, data)) {
            return true;
        }
    } else {
        rightVisited = true;
        if (right->intersect(ray, data)) {
            return true;
        }
    }
    if (!leftVisited && splittingPlane.distance(second) <= 0) {
        leftVisited = true;
        if (left->intersect(ray, data)) {
            return true;
        }
    }
    if (!rightVisited && splittingPlane.distance(second) > 0) {
        rightVisited = true;
        if (right->intersect(ray, data)) {
            return true;
        }
    }
    return false;
}

bool Node::intersectHere(const Ray ray, IntersectionData & data) const
{
    double distance = FLT_MAX;
    for (auto i : objectsWithBox) {
        IntersectionData l(false);
        if (i.object->rayIntersect(ray, l)) {
            if (boundingBox.hasPoint(l.intersection)) {
                if (distance > (ray.r0() - l.intersection).len()) {
                    distance = (ray.r0() - l.intersection).len();
                    data.obj = i.object;
                    data.intersection = l.intersection;
                    data.intersects = true;
                }
            }
        }
    }
    return data.intersects;
}
