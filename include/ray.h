#ifndef RAYH
#define RAYH
#include<vec3.h>
class ray
{
    public:
    ray(){}
    ray(const vec3&ori,const vec3&d,float time = 0.0);
    vec3 origin()const;
    vec3 direction()const;
    //返回光线产生的时间
    float time()const;
    //返回该光线传播t秒后的位置
    inline vec3 point_at_parameter(float t)const;
    inline vec3 at(float t)const;

    private:
    vec3 orig;//光线起点位置
    vec3 dir;//光线方向
    float tm;//表示该条射线产生的时间戳
};
ray::ray(const vec3&ori,const vec3&d,float time):orig(ori),dir(d),tm(time){}
vec3 ray::origin()const{return orig;}
vec3 ray::direction()const{return dir;}
float ray::time()const{return tm;}
inline vec3 ray::point_at_parameter(float t)const{return orig + t*dir;}
inline vec3 ray::at(float t)const{
    return point_at_parameter(t);
}
#endif