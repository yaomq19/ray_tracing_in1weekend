#include "ray.h"
ray::ray(const vec3&ori,const vec3&d,float time):orig(ori),dir(d),tm(time){}
vec3 ray::origin()const{return orig;}
vec3 ray::direction()const{return dir;}
float ray::time()const{return tm;}
inline vec3 ray::point_at_parameter(float t)const{return orig + t*dir;}
inline vec3 ray::at(float t)const{
    return point_at_parameter(t);
}