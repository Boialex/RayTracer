#include "KDTree.h"
#include <algorithm>

KDTree::KDNode::KDNode()
{
    left = NULL;
    right = NULL;
    box = Box();
    obj.clear();
}

long double KDTree::KDNode::findBorder(int axis, double & sah) const
{
    std::vector<long double> starts(obj.size());
    std::vector<long double> ends(obj.size());
    for (int i = 0; i < obj.size(); ++i) {
        Box b = obj[i]->getBox();
        switch (axis)
        {
        case 0:
            starts[i] = b.getA().x();
            ends[i] = b.getB().x();
            break;
        case 1:
            starts[i] = b.getA().y();
            ends[i] = b.getB().y();
            break;
        case 2:
            starts[i] = b.getA().z();
            ends[i] = b.getB().z();
            break;
        default:
            break;
        }
    }
    std::sort(starts.begin(), starts.end());
    std::sort(ends.begin(), ends.end());

    int n = obj.size();
    int i = 0, j = 0, current, ncur;
    double minsah = DBL_MAX;
    int minindex, vecindex;
    bool startismin = false;
    while (i < n || j < n) {
        double s;
        if (i == n) {
            s = emptycost + i * distleft(axis, ends[j]) + (n - j) * distright(axis, ends[j]);
            ncur = 1;
            current = j;
            ++j;
        }
        else if (j == n) {
            s = emptycost + i * distleft(axis, starts[i]) + (n - j) * distright(axis,starts[i]);
            ncur = 0;
            current = i;
            ++i;
        }
        else {
            if (starts[i] <= ends[j]) {
                current = i;
                ncur = 0;
                ++i;
            }
            else {
                current = j;
                ncur = 1;
                ++j;
            }
            if (ncur == 0)
                s = emptycost + i * distleft(axis, starts[current]) + (n - j) * distright(axis, starts[current]);
            else
                s = emptycost + i * distleft(axis, ends[current]) + (n - j) * distright(axis, ends[current]);
        }
        
        if (s < minsah) {
            minsah = s;
            minindex = current;
            vecindex = ncur;
        }
    }
    sah = minsah;
    if (ncur == 0)
        return starts[minindex];
    else
        return ends[minindex];
}

double KDTree::KDNode::distleft(int axis, long double border) const
{
    switch (axis)
    {
    case 0:
        return (border - box.getA().x());
        break;
    case 1:
        return (border - box.getA().y());
        break;
    case 2:
        return (border - box.getA().z());
        break;
    default:
        break;
    }
    return 0;
}

double KDTree::KDNode::distright(int axis, long double border) const
{
    switch (axis)
    {
    case 0:
        return (border - box.getB().x());
        break;
    case 1:
        return (border - box.getB().y());
        break;
    case 2:
        return (border - box.getB().z());
        break;
    default:
        break;
    }
    return 0;
}

void KDTree::KDNode::build()
{
    int axis = box.longestaxis();
    double sah;
    long double border = findBorder(axis, sah);
    if (sah < emptycost + box.longestlen() * obj.size())
        return;
    _border = border;
    left = std::unique_ptr<KDNode>(new KDNode);
    right = std::unique_ptr<KDNode>(new KDNode);
    switch (axis)
    {
    case 0:
        for (int i = 0; i < obj.size(); ++i) {
            Box b = obj[i]->getBox();
            if (b.getA().x() >= border)
                right->obj.push_back(obj[i]);
            else if (b.getB.x() <= border)
                left->obj.push_back(obj[i]);
            else {
                left->obj.push_back(obj[i]);
                right->obj.push_back(obj[i]);
            }
        }
        break;
    case 1:
        for (int i = 0; i < obj.size(); ++i) {
            Box b = obj[i]->getBox();
            if (b.getA().y() >= border)
                right->obj.push_back(obj[i]);
            else if (b.getB.y() <= border)
                left->obj.push_back(obj[i]);
            else {
                left->obj.push_back(obj[i]);
                right->obj.push_back(obj[i]);
            }
        }
        break;
    case 2:
        for (int i = 0; i < obj.size(); ++i) {
            Box b = obj[i]->getBox();
            if (b.getA().z() >= border)
                right->obj.push_back(obj[i]);
            else if (b.getB.z() <= border)
                left->obj.push_back(obj[i]);
            else {
                left->obj.push_back(obj[i]);
                right->obj.push_back(obj[i]);
            }
        }
        break;
    default:
        break;
    }
    left->build();
    right->build();
}

bool KDTree::KDNode::hit(const Ray & ray, Point3D & intersection)
{
    return false;
}

KDTree::KDTree(const std::vector<std::shared_ptr<IFigure>>& newobj)
{
    head = std::unique_ptr<KDNode>(new KDNode());
    head->obj = newobj;
    head->box = Box(newobj);
    head->build();
}

bool KDTree::hit(const Ray & ray, Point3D & intersection)
{
    return false;
}

