#include "Box.h"

Box::Box()
{
    _A = Point3D();
    _B = Point3D();
}

Box::Box(const Point3D A, const Point3D B)
{
    _A = A;
    _B = B;
}

Box::Box(const std::vector<std::shared_ptr<IFigure>>& objs)
{
    if (objs.size() == 0)
        return;
    long double xmin, xmax, ymin, ymax, zmin, zmax;
    Box b = objs[0]->getBox();
    xmin = b._A.x();
    xmax = b._B.x();
    ymin = b._A.y();
    ymax = b._B.y();
    zmin = b._A.z();
    zmax = b._B.z();
    for (int i = 1; i < objs.size(); ++i) {
        Box d = objs[i]->getBox();
        xmin = min(xmin, d._A.x());
        xmax = max(xmax, d._B.x());
        ymin = min(ymin, d._A.y());
        ymax = max(ymax, d._B.y());
        zmin = min(zmin, d._A.z());
        zmax = max(zmax, d._B.z());
    }
    _A = Point3D(xmin, ymin, zmin);
    _B = Point3D(xmax, ymax, zmax);
}

Point3D Box::getA() const
{
    return _A;
}

Point3D Box::getB() const
{
    return _B;
}

bool Box::intersect(const Ray ray) const
{
    if (ray.r0().x() >= _A.x()
        && ray.r0().x() <= _B.x()
        && ray.r0().y() >= _A.y()
        && ray.r0().y() <= _B.y()
        && ray.r0().z() >= _A.z()
        && ray.r0().z() <= _B.z())
        return true;

    double t_near = DBL_MIN;
    double t_far = DBL_MAX;
    double t1, t2;

    if (ray.a().x() != 0.0f) {
        t1 = (_A.x() - ray.r0().x()) / ray.a().x();
        t2 = (_B.x() - ray.r0().x()) / ray.a().x();
        if (t1 > t2)
            std::swap(t1, t2);
        t_near = max(t1, t_near);
        t_far = min(t2, t_far);
        if (t_near > t_far)
            return false;
        if (t_far < 0)
            return false;
    }
    if (ray.a().y() != 0.0f) {
        t1 = (_A.y() - ray.r0().y()) / ray.a().y();
        t2 = (_B.y() - ray.r0().y()) / ray.a().y();
        if (t1 > t2)
            std::swap(t1, t2);
        t_near = max(t1, t_near);
        t_far = min(t2, t_far);
        if (t_near > t_far)
            return false;
        if (t_far < 0)
            return false;
    }
    if (ray.a().z() != 0.0f) {
        t1 = (_A.z() - ray.r0().z()) / ray.a().z();
        t2 = (_B.z() - ray.r0().z()) / ray.a().z();
        if (t1 > t2)
            std::swap(t1, t2);
        t_near = max(t1, t_near);
        t_far = min(t2, t_far);
        if (t_near >= t_far)
            return false;
        if (t_far < 0)
            return false;
    }
    return (t_near < t_far && t_near >= 0);
}

int Box::longestaxis() const
{
    double x = _B.x() - _A.x();
    double y = _B.y() - _A.y();
    double z = _B.z() - _A.z();
    if (x >= y && x >= z)
        return 0;
    if (y >= x && y >= z)
        return 1;
    if (z >= x && z >= y)
        return 2;
    return 3;
}

double Box::longestlen() const
{
    double x = _B.x() - _A.x();
    double y = _B.y() - _A.y();
    double z = _B.z() - _A.z();
    return max(x, y, z);
}
