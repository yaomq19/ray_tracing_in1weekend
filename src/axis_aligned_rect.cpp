#include"axis_aligned_rect.h"
bool xy_rect::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-r.origin().z()) / r.direction().z();
    if (t <= t_min || t >= t_max)
        return false;
    auto x = r.origin().x() + t*r.direction().x();
    auto y = r.origin().y() + t*r.direction().y();
    if (x < x0 || x > x1 || y < y0 || y > y1)
        return false;
    rec.setU((x-x0)/(x1-x0));
    rec.setV((y-y0)/(y1-y0));
    rec.setTime(t);
    rec.setNormal(normal);
    rec.setMat(mp);
    rec.setPos(r.at(t));
    return true;
}
bool xz_rect::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-r.origin().y()) / r.direction().y();
    if (t <= t_min || t >= t_max)
        return false;
    auto x = r.origin().x() + t*r.direction().x();
    auto z = r.origin().z() + t*r.direction().z();
    if (x < x0 || x > x1 || z < z0 || z > z1)
        return false;
    rec.setU((x-x0)/(x1-x0));
    rec.setV((z-z0)/(z1-z0));
    rec.setTime(t);
    rec.setNormal(normal);
    rec.setMat(mp);
    rec.setPos(r.at(t));
    return true;
}
bool yz_rect::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    auto t = (k-r.origin().x()) / r.direction().x();
    if (t <= t_min || t >= t_max)
        return false;
    auto y = r.origin().y() + t*r.direction().y();
    auto z = r.origin().z() + t*r.direction().z();
    if (y < y0 || y > y1 || z < z0 || z > z1)
        return false;
    rec.setU( (y-y0)/(y1-y0));
    rec.setV((z-z0)/(z1-z0));
    rec.setTime(t);
    rec.setNormal(normal);
    rec.setMat(mp);
    rec.setPos(r.at(t));
    return true;
}
bool xy_rect::bounding_box(float time0, float time1, aabb& output_box) const {
    output_box = aabb(point3(x0,y0, k-0.0001), point3(x1, y1, k+0.0001));
    return true;
}