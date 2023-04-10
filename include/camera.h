#ifndef CAMERAH
#define CAMERAH
#include <ray.h>
class camera{
    public:
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    camera()
    {
        lower_left_corner = vec3(-2.0,-1.0,-1.0);//最左下角像素中心坐标
        horizontal = vec3(4.0,0.0,0.0);//4.0为水平方向步长
        vertical = vec3(0.0,2.0,0.0);//2.0为垂直方向步长
        origin = vec3(0.0,0.0,0.0);
    }
    ray get_ray(float u,float v){
        return ray(origin,lower_left_corner + u*horizontal + v*vertical-origin);
    }
};
#endif