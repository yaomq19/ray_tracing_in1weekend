#ifndef HITABLEH
#define HITABLEH
#include <ray.h>
#include <math.h>
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
    //返回从o点沿法线射出一个虚拟单位球中的单位球内的随机一点的坐标值
    vec3 diffuse(const vec3& o,const vec3&n)const{
        return o + n + random_in_unit_sphere();
    }
    //输入输入向量和平面单位法向量，返回反射向量
    //v为入射向量，可以不为单位向量
    //n为平面的单位法向量，必须是单位向量
    //返回值不一定为单位向量，当且仅当入射向量v为单位向量时返回值才为单位向量
    vec3 reflect(const vec3& v,const vec3&n)const{
        return v-2*dot(v,n)*n;
    }
    //折射
    //输入v为入射光线，n为平面单位法向量
    bool refract(const vec3& v,const vec3& n,float ni_over_nt,vec3& refracted)const{
        vec3 uv = unit_vector(v);
        float dt = dot(uv,n);
        float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
        if(discriminant > 0){
            refracted = ni_over_nt*(v - dt*n) - sqrt(discriminant)*n;
            return true;
        }else{
            return false;
        }
    }
};
class lambertian:public material{
    public:
    vec3 albedo;
    lambertian(const vec3& a):albedo(a){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
        vec3 target = diffuse(rec.p,rec.normal);
        scattered = ray(rec.p,target-rec.p);
        attenuation = albedo;
        return true;
    }
};
class metal:public material{
    public:
    vec3 albedo;
    float fuzz;
    metal(const vec3& a,float f = 1.0):albedo(a),fuzz(f){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
        vec3 reflected = reflect(unit_vector(r_in.direction()),rec.normal);
        scattered = ray(rec.p,reflected+fuzz*random_in_unit_sphere());
        attenuation = albedo;
        //保证了r_in不是从平面的背面射来的
        return (dot(scattered.direction(),rec.normal)>0);
    }
};
class dielectric:public material{
    public:
    float ref_idx;
    dielectric(float ri):ref_idx(ri){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scatter)const
    {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(),rec.normal);//向量reflect函数的输入是向量v和向量向量n
        float ni_over_nt;//射线refraction index ratio
        attenuation = vec3(1.0,1.0,1.0);//声明各种颜色的常数值，不一定
        vec3 refracted;//射线refraction ratio 或者是向量refract函数的输入是向量v和向量
        float reflect_prob;
        float cosine;
        if(dot(r_in.direction(),rec.normal) > 0){//如果向量向量n是反的 或者
            outward_normal = -rec.normal;//向量reflect函数的输入是向量v和向量向量n的反
            ni_over_nt = ref_idx;//ni_over_nt计算的是射线refraction index ratio 或者是
            cosine=ref_idx*dot(r_in.direction(),rec.normal)/r_in.direction().length();//cosine
        }
        else{//如果向量向量n是正的 或者 或者 向量reflect函数的输入是向量
            outward_normal = rec.normal;//向量reflect函数的输入是向量v和向量向量n的正
            ni_over_nt = 1.0f/ref_idx;//ni_over_nt计算的是射线refraction ratio
            cosine= -dot(r_in.direction(),rec.normal)/r_in.direction().length();//cosine 或者是1/
        }
        if(refract(r_in.direction(),outward_normal,ni_over_nt,refracted)){//向量refract
            reflect_prob  = schlick(cosine,ref_idx);//schlick函数的输入是射线cosine和射线refraction ratio
        }
        else{//如果不可逆 或者 射线refraction ratio 小于1 或者 射线refraction ratio 大
            scatter = ray(rec.p,reflected);//向量reflect函数的输入是向量v和向量向量n
            reflect_prob=1.0f;//这里的attenuation是一个空的向量，大于1的话，则是一个向量，其
        }
        if(drand48()<reflect_prob){
            scatter = ray(rec.p,reflected);//向量reflect函数的输入是向量v和向量向量n 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向
        }else{
            scatter = ray(rec.p,refracted);
        }
        return true;
    }
    float schlick(float cosine,float ref_idx)const{//射线refraction ratio 大于1的情况下，使用相同
        float r0 = (1-ref_idx)/(1+ref_idx);
        r0 = r0 *r0;//r0的值在0到1之间，这里应该是1。也就是说，
        return r0 + (1-r0)*pow((1-cosine),5);//pow函数的第二个参数是
    }
};
#endif