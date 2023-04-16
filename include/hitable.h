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
    private:
    vec3 normal; //命中点的单位法向量
    public:
    shared_ptr<material> mat_ptr;
    float u,v;//命中点的纹理坐标
    void setNormal( const vec3& vec);
    vec3 getNormal()const;
    
};

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

    /*
        返回既包围box0又包围box1的大包围盒
    */
    aabb surrounding_box(aabb box0, aabb box1) const;
};
class translate : public hitable {
    public:
        translate(shared_ptr<hitable> p, const vec3& displacement);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
    public:
        shared_ptr<hitable> ptr;
        vec3 offset;
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