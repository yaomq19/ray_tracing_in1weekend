#ifndef CAMERAH
#define CAMERAH
#include <ray.h>
#include<fstream>
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

camera::camera(const vec3&lookfrom, const vec3& lookat, const vec3& vup, float vfov, float aspect_ratio,
    float aperture,float focus_dist,float _time0,float _time1)//注：相机的画面范围完全由vfov和aspect_ratio两个参数决定，与其他参数无关
{
    //vfov垂直可视角（全部）
    //aspect_ratio宽高比
    //aperture为摄像机焦点到透镜的距离，反映了透镜折射程度，此值越小折射程度越大
    auto theta = (vfov) * M_PI / 180.f;//可视角的弧度表示
        auto h = tan(theta/2);//
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        back = (lookfrom - lookat).normalized();
        right = cross(vup, back).normalized();
        up = cross(back, right).normalized();

        //focus_dist:焦点到成像平面的距离
        origin = lookfrom;
        horizontal = focus_dist * viewport_width * right;
        vertical = focus_dist * viewport_height * up;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist * back;

        lens_radius = aperture / 2;//光圈半径为光圈直径的一半
        time0 = _time0;
        time1 = _time1;
}
ray camera::get_ray(float s,float t){
        //s和t是一个[0,1]之间的数，表示比例
        vec3 random = lens_radius * random_in_unit_disk();
            vec3 offset = right * random.x() + up * random.y();
            return ray(
                origin + offset,
                lower_left_corner + s*horizontal + t*vertical - origin - offset,
                random_float(time0, time1)
            );
    }
#endif