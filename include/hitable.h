#ifndef HITABLEH
#define HITABLEH
#include <ray.h>
class material;
struct hit_record{
    float t;//命中记录的时间
    vec3 p; //命中点的位置
    vec3 normal; //命中点的单位法向量
    material* mat_ptr;
};//For forward declarations.  This is a structure.  It is not an actual class.  It is just a way of passing data

//抽象量，所有射线可以命中的物体的抽象
class hitable{
    public:
    //抽象方法：判断时间作用域在tmin和tmax之间的射线r与当前物体是否相交
    //如果不相交则返回false
    //如果相交则返回true，并在rec处以引用返回命中纪录
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const = 0;  //The ray intersect
};


class material{
    public:
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const = 0;
};
class lambertian:public material{
    public:
    vec3 albedo;
    lambertian(const vec3& a):albedo(a){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
        vec3 target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = ray(rec.p,target-rec.p);
        attenuation = albedo;
        return true;
    }
};
class metal:public material{
    public:
    vec3 albedo;
    metal(const vec3& a):albedo(a){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
        vec3 temp = unit_vector(r_in.direction());
        vec3 reflected = reflect(temp,rec.normal);
        scattered = ray(rec.p,reflected);
        attenuation = albedo;
        //保证了r_in不是从平面的背面射来的
        return (dot(scattered.direction(),rec.normal)>0);
    }
    private:
    //输入输入向量和平面单位法向量，返回反射向量
    //v为入射向量，可以不为单位向量
    //n为平面的单位法向量，必须是单位向量
    //返回值不一定为单位向量，当且仅当入射向量v为单位向量时返回值才为单位向量
    vec3 reflect(const vec3& v,const vec3&n)const{
        return v-2*dot(v,n)*n;
    }
};

#endif