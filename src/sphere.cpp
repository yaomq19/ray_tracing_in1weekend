#include "sphere.h"
#define pi (3.1415926535)
sphere::sphere(){}
sphere::sphere(vec3 cen,float r,shared_ptr<material> m):center(cen),radius(r),mat_ptr(m){}
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
            rec.setNormal(outward_normal);
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
void sphere::get_sphere_uv(const point3& p, float& u, float& v) {
    auto theta = acos(-p.y());
    auto phi = atan2(-p.z(), p.x()) + pi;
    u = phi / (2*pi);
    v = theta / pi;
}