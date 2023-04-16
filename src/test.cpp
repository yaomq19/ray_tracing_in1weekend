#include<iostream>
#include<time.h>
#include<memory>
#include "material.h"
#include "bvh.h"
#include "axis_aligned_rect.h"
#include "vec3.h"
#include "sphere.h"
#include "hitable_list.h"
#include "movingSphere.h"
#include "camera.h"
#include "renderer.h"
#include "box.h"
hitable_list test() {
    hitable_list objects;

    shared_ptr<material> red   = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    shared_ptr<material> green   = make_shared<lambertian>(color(0.00, 0.75, 0.55));
    shared_ptr<material> light = make_shared<diffuse_light>(color(3, 3, 3));

    objects.add(make_shared<sphere>(vec3(0,0,-6), 3,  green));
    objects.add(make_shared<xy_rect>(-5, 5, -5, 5, -6, red,vec3(0,0,1)));//红色平面
    objects.add(make_shared<xy_rect>(-5, 5, -5, 5, 6, light,vec3(0,0,-1)));//平面光源
    return objects;
}
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    srand(time(NULL));
    //world
    hitable_list world = test();//Create a world containing the two objects.  You can use any other objects you like.
    color background(0,0,0);

    //camera
    vec3 lookfrom(0,0,0);//相机位置
    vec3 lookat(0,0,-1);//相机目标点
    vec3 vup(0,1,0);//相机up向量
    auto vfov = 90;
    auto aspect_ratio = 1;
    float aperture = 0.0;//相机透镜光圈大小,越大越模糊
    float dist_to_focus = 10.0;//表示摄像机焦点到透镜的距离
    float exposure_time_start = 0.0;//曝光开始时间
    float exposure_time_end = 1.0;//曝光结束时间
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, exposure_time_start, exposure_time_end);
    //renderer
    int image_width = 200;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    const int max_depth = 50;//递归最大深度
    int samples_per_pixel = 100;
    renderer ren(world,cam,image_width,image_height,samples_per_pixel,max_depth);
    ren.setBackground(color(0,0,0));
    //ren.EnableBVH();
    ren.render(argv[1]);
    return 0;
}