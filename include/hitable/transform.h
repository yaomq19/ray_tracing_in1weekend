#ifndef TRANSFORM_H
#define TRANSFORM_H
#include"hitable.h"
class translate : public hitable {
    public:
        /*
            使用 需要平移的物体的指针 和 偏移量 进行构造
        */
        translate(shared_ptr<hitable> p, const vec3& displacement);
        /*
            检查作用域在[t_min,t_max]间的射线ray与平移后的物体是否有交点
            if(有交点)return true and 在rec处返回交点
            else return false
        */
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        /*
            检查平移后的物体是否有bounding_box
            if(有)return true and 在output_box处返回该bounding_box
            else return false
        */
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
    public:
        shared_ptr<hitable> ptr;//指向平移前的物体的指针
        vec3 offset;//平移偏移量，由平移前指向平移后
};
class rotate_y : public hitable {
    public:
        rotate_y(shared_ptr<hitable> p, float angle);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
    public:
        shared_ptr<hitable> ptr;
        float sin_theta;
        float cos_theta;
        bool hasbox;
        aabb bbox;
};
#endif