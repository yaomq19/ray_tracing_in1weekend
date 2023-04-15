#ifndef HITABLEH
#define HITABLEH
#include <ray.h>
#include <math.h>
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
    //抽象方法：判断时间作用域在tmin和tmax之间的射线r与当前物体是否相交
    //如果不相交则返回false
    //如果相交则返回true，并在rec处以引用返回命中纪录
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const = 0;  //The ray intersect
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

#endif