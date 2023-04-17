#include "constant_medium.h"
constant_medium::constant_medium(shared_ptr<hitable> b, float d, shared_ptr<texture> a)
    : boundary(b),
        neg_inv_density(-1/d),
        phase_function(make_shared<isotropic>(a))
    {}
constant_medium::constant_medium(shared_ptr<hitable> b, float d, color c)
    : boundary(b),
        neg_inv_density(-1/d),
        phase_function(make_shared<isotropic>(c))
    {}
bool constant_medium::bounding_box(float time0, float time1, aabb& output_box) const {
    return boundary->bounding_box(time0, time1, output_box);
}
bool constant_medium::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    // Print occasional samples when debugging. To enable, set enableDebug true.
    const bool enableDebug = false;
    const bool debugging = enableDebug && random_float() < 0.00001;

    hit_record rec1, rec2;

    if (!boundary->hit(r, -MAXFLOAT, MAXFLOAT, rec1))
        return false;

    if (!boundary->hit(r, rec1.getTime()+0.0001, MAXFLOAT, rec2))
        return false;

    if (debugging) std::cerr << "\nt_min=" << rec1.getTime() << ", t_max=" << rec2.getTime() << '\n';

    if (rec1.getTime() < t_min) rec1.setTime(t_min);
    if (rec2.getTime() > t_max) rec2.setTime(t_max);

    if (rec1.getTime() >= rec2.getTime())
        return false;

    if (rec1.getTime() < 0)
        rec1.getTime() = 0;

    const auto ray_length = r.direction().length();
    const auto distance_inside_boundary = (rec2.getTime() - rec1.getTime()) * ray_length;
    const auto hit_distance = neg_inv_density * log(random_float());

    if (hit_distance > distance_inside_boundary)
        return false;

    rec.setTime(rec1.getTime() + hit_distance / ray_length);
    rec.setPos(r.at(rec.getTime()));

    // if (debugging) {
    //     std::cerr << "hit_distance = " <<  hit_distance << '\n'
    //               << "rec.t = " <<  rec.getTime() << '\n'
    //               << "rec.p = " <<  rec.getPos() << '\n';
    // }

    rec.setNormal(vec3(1,0,0));  // arbitrary
    //rec.front_face = true;     // also arbitrary
    rec.setMat(phase_function);

    return true;
}