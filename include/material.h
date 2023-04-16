#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "texture.h"
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
    virtual color emitted(double u, double v, const point3& p) const {
            return color(0,0,0);
    }
};
class lambertian:public material{
    public:
    shared_ptr<texture> albedo;
    lambertian(const color& a) : albedo(make_shared<solid_color>(a)) {}
    lambertian(shared_ptr<texture> a) : albedo(a) {}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const{
        auto scatter_direction = rec.normal + random_in_unit_sphere();
        /*  如果散射后的光线方向非常接近于零向量（即光线散射后几乎不改变方向），
            那么就将光线的方向设置为表面的法向量。
            这是因为如果光线散射后的方向变化很小，
            那么散射后的光线仍然会沿着原来的方向前进，
            这会导致渲染结果出现一些奇怪的现象。*/
        if (scatter_direction.near_zero())
                scatter_direction = rec.normal;
        //注意不改变光线的产生时间，也就是把反射后的光线看成与之前的同一条
        scattered = ray(rec.p, scatter_direction, r_in.time());
        //击中点材质的固有色由纹理产生
        attenuation = albedo->value(rec.u, rec.v, rec.p);
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
        scattered = ray(rec.p,reflected+fuzz*random_in_unit_sphere(),r_in.time());
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
            scatter = ray(rec.p,reflected,r_in.time());//向量reflect函数的输入是向量v和向量向量n
            reflect_prob=1.0f;//这里的attenuation是一个空的向量，大于1的话，则是一个向量，其
        }
        if(drand48()<reflect_prob){
            scatter = ray(rec.p,reflected,r_in.time());//向量reflect函数的输入是向量v和向量向量n 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向量v和向量向量n的反 或者是向
        }else{
            scatter = ray(rec.p,refracted,r_in.time());
        }
        return true;
    }
    float schlick(float cosine,float ref_idx)const{//射线refraction ratio 大于1的情况下，使用相同
        float r0 = (1-ref_idx)/(1+ref_idx);
        r0 = r0 *r0;//r0的值在0到1之间，这里应该是1。也就是说，
        return r0 + (1-r0)*pow((1-cosine),5);//pow函数的第二个参数是
    }
};
class diffuse_light : public material  {
    public:
        diffuse_light(shared_ptr<texture> a) : emit(a) {}
        diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}

        //永远返回false，即diffuse_light不判交，不反射，只发光
        virtual bool scatter(
            const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
        ) const override {
            return false;
        }

        virtual color emitted(double u, double v, const point3& p) const override {
            return emit->value(u, v, p);
        }

    public:
        shared_ptr<texture> emit;
};
#endif