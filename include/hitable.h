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
public:
    inline void setNormal(const vec3& norm){normal = norm.normalized();}
    inline vec3 getNormal()const{return normal;}
    inline vec3& getNormal(){return normal;}

    inline void setTime(float time){t=time;}
    inline float getTime()const{return t;}
    inline float& getTime(){return t;}

    inline void setPos(const vec3& pos){p=pos;}
    inline vec3 getPos()const{return p;}
    inline vec3& getPos(){return p;}

    inline void setU(float uu){u=uu;}
    inline float getU()const{return u;}
    inline float& getU(){return u;}

    inline void setV(float vv){v=vv;}
    inline float getV()const{return v;}
    inline float& getV(){return v;}

    inline void setMat(shared_ptr<material> ptr){mat_ptr=ptr;}
    inline shared_ptr<material> getMat()const{return mat_ptr;}
    inline shared_ptr<material>& getMat(){return mat_ptr;}
private:
    float t;//命中记录的时间
    vec3 p; //命中点的位置
    vec3 normal; //命中点的单位法向量
    float u,v;//命中点的纹理坐标
    shared_ptr<material> mat_ptr;//命中点的材质
};

//所有射线可以命中的物体的抽象
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
};

#endif