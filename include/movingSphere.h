#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H
#include <hitable.h>
class moving_sphere : public hitable {
    public:
        moving_sphere() {}
        moving_sphere(
            vec3 cen0, vec3 cen1, float _time0, float _time1, float r, shared_ptr<material> m)
            : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
        {};

        virtual bool hit(
            const ray& r, float t_min, float t_max, hit_record& rec) const override;

        vec3 center(float time) const;

    public:
        vec3 center0, center1;
        float time0, time1;
        float radius;
        shared_ptr<material> mat_ptr;
};

vec3 moving_sphere::center(float time) const {
    return center0 + ((time - time0) / (time1 - time0))*(center1 - center0);
}
#endif