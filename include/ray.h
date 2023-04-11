#ifndef RAYH
#define RAYH
#include<vec3.h>
class ray
{
    public:
    ray(){}
    ray(const vec3&ori,const vec3&d,float time = 0.0):orig(ori),dir(d),tm(time){}
    vec3 origin()const{return orig;}
    vec3 direction()const{return dir;}
    float time()const{return tm;}
    //返回该光线传播t秒后的位置
    inline vec3 point_at_parameter(float t)const{return orig + t*dir;}
    inline vec3 at(float t){
        return point_at_parameter(t);
    }

    private:
    vec3 orig;//光线起点位置
    vec3 dir;//光线方向
    float tm;
};
#endif