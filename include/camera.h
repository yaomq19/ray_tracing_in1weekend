#ifndef CAMERAH
#define CAMERAH
#include <ray.h>
#include<fstream>
vec3 random_in_unit_disk()
{
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(),drand48(),0) - vec3(1,1,0);
    }while(dot(p,p)>=1.0);
    return p;
}
float random_float(float t0,float t1)
{
    float ratio = (float)(rand()%1000)/1000.f;
    return t0 + ratio * (t1-t0);
}
class camera{
    private:
    vec3 origin;//相机位置
    vec3 u,v,w;
    vec3 lower_left_corner;//最左下角像素中心坐标
    vec3 horizontal;//视野水平方向总长度
    vec3 vertical;//视野垂直方向总长度

    float lens_radius;
    float time0,time1;// shutter open/close times
    
    public:
    //相机位置，相机目视点，相机up向量，垂直可视角，视野宽高比，成像平面与相机原点距离，水平分辨率，垂直分辨率
    camera(const vec3&lookfrom, const vec3& lookat, const vec3& vup, float vfov, float aspect_ratio,
    float aperture,float focus_dist,float _time0 = 0,float _time1 = 0)
    {
        auto theta = (vfov) * M_PI / 180.f;
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            w = unit_vector(lookfrom - lookat);
            u = unit_vector(cross(vup, w));
            v = cross(w, u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture / 2;
            time0 = _time0;
            time1 = _time1;
    }
    ray get_ray(float s,float t){
        vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u * rd.x() + v * rd.y();

            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset,
                random_float(time0, time1)
            );
    }
};
#endif