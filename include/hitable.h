#ifndef HITABLEH
#define HITABLEH
#include <ray.h>
#include <math.h>
#include <memory>
using namespace std;
class material;
struct hit_record{
    float t;//命中记录的时间
    vec3 p; //命中点的位置
    vec3 normal; //命中点的单位法向量
    shared_ptr<material> mat_ptr;

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
};

#endif