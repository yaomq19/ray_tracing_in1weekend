#ifndef CAMERAH
#define CAMERAH
#include <ray.h>
#include<fstream>
class camera{
    public:
    vec3 origin;//相机位置
    vec3 direction;//相机朝向
    vec3 up;//up向量 

    vec3 lower_left_corner;//最左下角像素中心坐标
    vec3 horizontal;//视野水平方向总长度
    vec3 vertical;//视野垂直方向总长度
    //相机位置，相机目视点，相机up向量，垂直可视角，视野宽高比，成像平面与相机原点距离，水平分辨率，垂直分辨率
    camera(const vec3&lookfrom, const vec3& lookat, const vec3& vup, float fov, float aspect, float near)
    {
        vec3 u,v,w;
        float theta = fov * M_PI / 180.0f;
        float half_height = tan(theta / 2.0f) * near;
        float half_width = half_height * aspect;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u  = unit_vector(cross(vup, w));
        v = 	cross(w,u);
        lower_left_corner = origin - w*near - half_width*u - half_height*v;
        horizontal = 2*half_width*u;
        vertical = 2*half_height*v;
    }
    ray get_ray(float u,float v){
        return ray(origin,lower_left_corner + u*horizontal + v*vertical-origin);
    }
};
#endif