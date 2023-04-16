#ifndef CAMERAH
#define CAMERAH
#include <ray.h>
#include <fstream>
#include "myMath.h"
class camera{
    public:
    camera(const vec3&lookfrom, const vec3& lookat, const vec3& vup, float vfov, float aspect_ratio,
    float aperture,float focus_dist,float _time0 = 0,float _time1 = 0);
    ray get_ray(float s,float t);

    private:
    vec3 origin;//相机位置
    vec3 right,up,back;//相机的实际右、上、后向量，是单位向量
    vec3 lower_left_corner;//最左下角像素中心坐标
    vec3 horizontal;//指向水平视野正右方，其长度表示成像平面的横向宽度
    vec3 vertical;//指向水平视野正上方，其长度表示成像平面的纵向长度
    float lens_radius;//光圈半径
    float time0,time1;//快门起始时间和结束时间,该世界的时间起点为摄像机，即射线从相机出发那一刻为原点0
};


#endif