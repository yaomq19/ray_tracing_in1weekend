#include "hitable/movingSphere.h"
moving_sphere::moving_sphere() {}
moving_sphere::moving_sphere(
    vec3 cen0, vec3 cen1, float _time0, float _time1, float r, shared_ptr<material> m)
    : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
{};
vec3 moving_sphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}
bool moving_sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.setTime(root);
    rec.setPos(r.at(rec.getTime()));
    auto outward_normal = (rec.getPos() - center(r.time())) / radius;
    rec.setNormal(outward_normal);
    rec.setMat(mat_ptr);

    return true;
}
bool moving_sphere::bounding_box(float _time0, float _time1, aabb& output_box) const {
    aabb box0(center(_time0) - vec3(radius, radius, radius),
        center(_time0) + vec3(radius, radius, radius));
    aabb box1(center(_time1) - vec3(radius, radius, radius),
        center(_time1) + vec3(radius, radius, radius));
    output_box = surrounding_box(box0, box1);
    return true;
}