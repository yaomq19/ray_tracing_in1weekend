#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H
#include <hitable.h>
#include <memory>
#include "aabb.h"
//移动的小球
aabb surrounding_box(aabb box0, aabb box1);
class moving_sphere : public hitable {
    public:
        moving_sphere() {}
        moving_sphere(
            vec3 cen0, vec3 cen1, float _time0, float _time1, float r, shared_ptr<material> m)
            : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m)
        {};

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float _time0, float _time1, aabb& output_box) const override;
        
        vec3 center(float time) const;

    public:
    //小球在time=time0时的球心为center0
    //在time=time1时的球心为center1
        vec3 center0, center1;
        float time0, time1;
        //小球半径
        float radius;
        //小球的材质指针
        shared_ptr<material> mat_ptr;
};


#endif