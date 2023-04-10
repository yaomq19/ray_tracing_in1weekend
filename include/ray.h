#ifndef RAYH
#define RAYH
#include<vec3.h>
class ray
{
    public:
    vec3 A;//光线起点位置
    vec3 B;//光线方向

    ray(){}
    ray(const vec3&a,const vec3&b){
        A=a;
        B=unit_vector(b);
    }
    vec3 origin()const{return A;}
    vec3 direction()const{return B;}
    //返回该光线传播t秒后的位置
    vec3 point_at_parameter(float t)const{return A + t*B;}
};
#endif