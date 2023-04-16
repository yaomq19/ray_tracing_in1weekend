#ifndef HITABLEH
#define HITABLEH
#include <ray.h>
#include <math.h>
#include "myMath.h"
#include <memory>
#include "aabb.h"
using namespace std;
class material;
struct hit_record{
    float t;//命中记录的时间
    vec3 p; //命中点的位置
    vec3 normal; //命中点的单位法向量
    shared_ptr<material> mat_ptr;
    float u,v;//命中点的纹理坐标
    void set_face_normal(const ray& r, const vec3& vec)
    {
        normal = vec.normalized();
    }
};//For forward declarations.  This is a structure.  It is not an actual class.  It is just a way of passing data

//抽象量，所有射线可以命中的物体的抽象
class hitable{
    public:
    /*
        判断时间作用域在tmin和tmax之间的射线r与当前物体是否相交,相交返回true,否则返回false
        并在rec处以引用返回命中纪录
    */
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const = 0; 

    /*
        判断该物体是否有bounding_box，有则返回true，否则返回false，并再output_box处以引用返回该包围盒
        time0 and time1是物体运动的开始时间和结束时间，用来计算output_box的大小
    */
    virtual bool bounding_box(float time0, float time1, aabb& output_box) const = 0;
    //返回既包围box0又包围box1的大包围盒
    aabb surrounding_box(aabb box0, aabb box1) const{
        vec3 small(fmin(box0.min().x(), box1.min().x()),
                    fmin(box0.min().y(), box1.min().y()),
                    fmin(box0.min().z(), box1.min().z()));
        vec3 big(fmax(box0.max().x(), box1.max().x()),
                fmax(box0.max().y(), box1.max().y()),
                fmax(box0.max().z(), box1.max().z()));
        return aabb(small,big);
    }
};
class translate : public hitable {
    public:
        translate(shared_ptr<hitable> p, const vec3& displacement)
            : ptr(p), offset(displacement) {}

        virtual bool hit(
            const ray& r, float t_min, float t_max, hit_record& rec) const override;

        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

    public:
        shared_ptr<hitable> ptr;
        vec3 offset;
};
bool translate::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    ray moved_r(r.origin() - offset, r.direction(), r.time());
    if (!ptr->hit(moved_r, t_min, t_max, rec))
        return false;

    rec.p += offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}
bool translate::bounding_box(float time0, float time1, aabb& output_box) const {
    if (!ptr->bounding_box(time0, time1, output_box))
        return false;

    output_box = aabb(
        output_box.min() + offset,
        output_box.max() + offset);

    return true;
}

class rotate_y : public hitable {
    public:
        rotate_y(shared_ptr<hitable> p, float angle);

        virtual bool hit(
            const ray& r, float t_min, float t_max, hit_record& rec) const override;

        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
            output_box = bbox;
            return hasbox;
        }

    public:
        shared_ptr<hitable> ptr;
        float sin_theta;
        float cos_theta;
        bool hasbox;
        aabb bbox;
};
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

    auto p = rec.p;
    auto normal = rec.normal;

    p[0] =  cos_theta*rec.p[0] + sin_theta*rec.p[2];
    p[2] = -sin_theta*rec.p[0] + cos_theta*rec.p[2];

    normal[0] =  cos_theta*rec.normal[0] + sin_theta*rec.normal[2];
    normal[2] = -sin_theta*rec.normal[0] + cos_theta*rec.normal[2];

    rec.p = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}
#endif