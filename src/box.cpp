#include "box.h"
box::box(const point3& p0, const point3& p1, shared_ptr<material> ptr) {
    box_min = p0;
    box_max = p1;

    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr,vec3(0,0,1)));//前面
    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr,vec3(0,0,-1)));//后面

    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr,vec3(0,1,0)));//顶面
    sides.add(make_shared<xz_rect>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr,vec3(0,-1,0)));//底面

    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr,vec3(1,0,0)));//右面
    sides.add(make_shared<yz_rect>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr,vec3(-1,0,0)));//左面
}
bool box::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    return sides.hit(r, t_min, t_max, rec);
}
bool box::bounding_box(float time0, float time1, aabb& output_box) const {
    //bounding_box就是该盒子本身
    output_box = aabb(box_min, box_max);
    return true;
}