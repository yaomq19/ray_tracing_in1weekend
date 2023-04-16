#ifndef MATERIAL_H
#define MATERIAL_H

#include "vec3.h"
#include "ray.h"
#include "hitable.h"
#include "texture.h"
class material{
    public:
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const = 0;
    virtual color emitted(double u, double v, const point3& p) const;
};
class lambertian:public material{
    public:
    shared_ptr<texture> albedo;
    lambertian(const color& a) : albedo(make_shared<solid_color>(a)) {}
    lambertian(shared_ptr<texture> a) : albedo(a) {}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const;
};
class metal:public material{
    public:
    metal(const vec3& a,float f = 1.0):albedo(a),fuzz(f){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const;
    private:
    //反射
    vec3 reflect(const vec3& v,const vec3&n)const;
    vec3 albedo;
    float fuzz;
};
class dielectric:public material{
    public:
    float ref_idx;
    dielectric(float ri):ref_idx(ri){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scatter)const;
    private:
    //反射
    vec3 reflect(const vec3& v,const vec3&n)const;
    //折射,输入v为入射光线，n为平面单位法向量
    bool refract(const vec3& v,const vec3& n,float ni_over_nt,vec3& refracted)const;
    float schlick(float cosine,float ref_idx)const;
};
class diffuse_light : public material  {
    public:
        diffuse_light(shared_ptr<texture> a) : emit(a) {}
        diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
        virtual color emitted(double u, double v, const point3& p) const override;
    public:
        shared_ptr<texture> emit;
};













#endif