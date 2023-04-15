#ifndef SPHEREH
#define SPHEREH
#include <hitable.h>
#include <memory>
using namespace std;
class sphere:public hitable{
    public:
    vec3 center;//球体中心坐标
    float radius;//球体半径
    shared_ptr<material> mat_ptr;

    sphere(){}
    sphere(vec3 cen,float r,shared_ptr<material> m):center(cen),radius(r),mat_ptr(m){}
    //抽象方法hitable::hit的重写，具体实现了该方法
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    
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
            rec.normal = (rec.p - center) / radius; 
            rec.mat_ptr = mat_ptr;
            return true;
        }
    }        
    return false;
}
#endif