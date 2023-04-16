#ifndef AARECT_H
#define AARECT_H
#include "vec3.h"
#include "hitable.h"
class xy_rect : public hitable {
    public:
        xy_rect() {}
        xy_rect(float _x0, float _x1, float _y0, float _y1, float _k, 
            shared_ptr<material> mat,vec3 n)
            : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat),normal(n) {};
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
    private:
        shared_ptr<material> mp;
        float x0, x1, y0, y1, k;
        vec3 normal;
};
class xz_rect : public hitable {
    public:
        xz_rect() {}

        xz_rect(float _x0, float _x1, float _z0, float _z1, float _k,
            shared_ptr<material> mat,vec3 n)
            : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat),normal(n) {};

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
            // The bounding box must have non-zero width in each dimension, so pad the Y
            // dimension a small amount.
            output_box = aabb(point3(x0,k-0.0001,z0), point3(x1, k+0.0001, z1));
            return true;
        }

    public:
        shared_ptr<material> mp;
        float x0, x1, z0, z1, k;
        vec3 normal;
};
class yz_rect : public hitable {
    public:
        yz_rect() {}

        yz_rect(float _y0, float _y1, float _z0, float _z1, float _k,
            shared_ptr<material> mat,vec3 n)
            : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat),normal(n) {};

        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;

        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
            // The bounding box must have non-zero width in each dimension, so pad the X
            // dimension a small amount.
            output_box = aabb(point3(k-0.0001, y0, z0), point3(k+0.0001, y1, z1));
            return true;
        }

    public:
        shared_ptr<material> mp;
        float y0, y1, z0, z1, k;
        vec3 normal;
};

#endif