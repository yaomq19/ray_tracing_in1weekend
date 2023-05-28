#include "hitable/transform.h"
translate::translate(shared_ptr<hitable> p, const vec3& displacement): ptr(p), offset(displacement) {}
bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    /*
    先将光线 r 沿着相反的方向平移 offset，然后调用 ptr->hit 计算平移后的光线是否与包含的物体相交，
    并将结果存储在 rec 中。最后，将 rec 中的交点 p 再平移回原来的位置。
    */
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;
    rec.setPos(rec.getPos()+ offset);
    return true;
}
bool translate::bounding_box(float time0, float time1, aabb& output_box) const {
    /*
        首先计算出平移之前物体的包围盒 output_box，然后将其平移 offset，
        得到平移后的包围盒。
    */
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;
    output_box = aabb(
        output_box.min() + offset,
        output_box.max() + offset);
    return true;
}
rotate_y::rotate_y(shared_ptr<hitable> p, float angle) : ptr(p) {
    auto radians = degrees_to_radians(angle);
    sin_theta = sin(radians);
    cos_theta = cos(radians);
    hasbox = ptr->bounding_box(0, 1, bbox);

    point3 min( MAXFLOAT,  MAXFLOAT,  MAXFLOAT);
    point3 max(-MAXFLOAT, -MAXFLOAT, -MAXFLOAT);

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto x = i*bbox.max().x() + (1-i)*bbox.min().x();
                auto y = j*bbox.max().y() + (1-j)*bbox.min().y();
                auto z = k*bbox.max().z() + (1-k)*bbox.min().z();

                auto newx =  cos_theta*x + sin_theta*z;
                auto newz = -sin_theta*x + cos_theta*z;

                vec3 tester(newx, y, newz);

                for (int c = 0; c < 3; c++) {
                    min[c] = fmin(min[c], tester[c]);
                    max[c] = fmax(max[c], tester[c]);
                }
            }
        }
    }

    bbox = aabb(min, max);
}
bool rotate_y::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    auto origin = r.origin();
    auto direction = r.direction();

    origin[0] = cos_theta*r.origin()[0] - sin_theta*r.origin()[2];
    origin[2] = sin_theta*r.origin()[0] + cos_theta*r.origin()[2];

    direction[0] = cos_theta*r.direction()[0] - sin_theta*r.direction()[2];
    direction[2] = sin_theta*r.direction()[0] + cos_theta*r.direction()[2];

    ray rotated_r(origin, direction, r.time());

    if (!ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.getPos();
    auto normal = rec.getNormal();

    p[0] =  cos_theta*rec.getPos()[0] + sin_theta*rec.getPos()[2];
    p[2] = -sin_theta*rec.getPos()[0] + cos_theta*rec.getPos()[2];

    normal[0] =  cos_theta*rec.getNormal()[0] + sin_theta*rec.getNormal()[2];
    normal[2] = -sin_theta*rec.getNormal()[0] + cos_theta*rec.getNormal()[2];

    rec.setPos(p);
    rec.setNormal( normal);

    return true;
}
bool rotate_y::bounding_box(float time0, float time1, aabb& output_box) const{
    output_box = bbox;
    return hasbox;
}