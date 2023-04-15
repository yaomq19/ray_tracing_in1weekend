#ifndef SPHEREH
#define SPHEREH
#include <hitable.h>
#include <memory>
using namespace std;
#define pi (3.1415926535)
class sphere:public hitable{
    public:
    vec3 center;//球体中心坐标
    float radius;//球体半径
    shared_ptr<material> mat_ptr;

    sphere(){}
    sphere(vec3 cen,float r,shared_ptr<material> m):center(cen),radius(r),mat_ptr(m){}
    //抽象方法hitable::hit的重写，具体实现了该方法
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

    private:
        static void get_sphere_uv(const point3& p, float& u, float& v) {
            // p: a given point on the sphere of radius one, centered at the origin.
            // u: returned value [0,1] of angle around the Y axis from X=-1.
            // v: returned value [0,1] of angle from Y=-1 to Y=+1.
            //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
            //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
            //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

            auto theta = acos(-p.y());
            auto phi = atan2(-p.z(), p.x()) + pi;

            u = phi / (2*pi);
            v = theta / pi;
        }
};
bool sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {   
    vec3 oc = r.origin() - center;        
    float a = dot(r.direction(), r.direction());     
    float b = dot(oc, r.direction());      
    float c = dot(oc, oc) - radius * radius;     
    float dis = b * b - a * c;       
    if (dis > 0.0) {      
        float t = (-b - sqrt(dis)) / a;        
        if (t_min < t && t < t_max) {     
            rec.t = t;      
            rec.p = r.point_at_parameter(rec.t); 
            vec3 outward_normal  = (rec.p - center) / radius; 
            rec.set_face_normal(r, outward_normal);
            get_sphere_uv(outward_normal, rec.u, rec.v);
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }        
    return false;
}
bool sphere::bounding_box(float time0, float time1, aabb& output_box) const {
    output_box = aabb(
        center - vec3(radius, radius, radius),
        center + vec3(radius, radius, radius));
    return true;
}
#endif