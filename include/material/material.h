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

//漫反射材质
class lambertian:public material{
public:
    lambertian(const color& a) : albedo(make_shared<solid_color>(a)) {}
    lambertian(shared_ptr<texture> a) : albedo(a) {}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const;

private:
    shared_ptr<texture> albedo;//固有纹理
};
//金属材质（不使用纹理）
class metal:public material{
public:
    metal(const vec3& a,float f = 1.0):albedo(a),fuzz(f){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scattered)const;
    
private:
    vec3 reflect(const vec3& v,const vec3&n)const;
    vec3 albedo;//固有纯色
    float fuzz;//表面模糊度，越大越模糊
};
//透明折射体材质（不使用纹理）
class dielectric:public material{
public:
    dielectric(float ri):ref_idx(ri){}
    virtual bool scatter(const ray& r_in,const hit_record& rec,vec3& attenuation,ray& scatter)const;

private:
    float ref_idx;//折射率
    vec3 reflect(const vec3& v,const vec3&n)const;
    bool refract(const vec3& v,const vec3& n,float ni_over_nt,vec3& refracted)const;
    float schlick(float cosine,float ref_idx)const;
};
//漫反射光源材质
class diffuse_light : public material  {
    public:
        diffuse_light(shared_ptr<texture> a) : emit(a) {}
        diffuse_light(color c) : emit(make_shared<solid_color>(c)) {}
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
        virtual color emitted(double u, double v, const point3& p) const override;
    public:
        shared_ptr<texture> emit;//发光纹理
};

class isotropic : public material {
    public:
        isotropic(color c);
        isotropic(shared_ptr<texture> a);
        virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
    private:
        shared_ptr<texture> albedo;
};











#endif