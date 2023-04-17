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
#include "transform.h"
#include "constant_medium.h"
#include <chrono>


hitable_list final_scene() {
    hitable_list boxes1;
    auto ground = make_shared<lambertian>(color(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = random_float(1,101);
            auto z1 = z0 + w;

            boxes1.add(make_shared<box>(point3(x0,y0,z0), point3(x1,y1,z1), ground));
        }
    }

    hitable_list objects;

    objects.add(make_shared<bvh_node>(boxes1, 0, 1));//

    auto light = make_shared<diffuse_light>(color(7, 7, 7));
    objects.add(make_shared<xz_rect>(123, 423, 147, 412, 554, light,vec3(0,-1,0)));//

    auto center1 = point3(400, 400, 200);
    auto center2 = center1 + vec3(30,0,0);
    auto moving_sphere_material = make_shared<lambertian>(color(0.7, 0.3, 0.1));
    objects.add(make_shared<moving_sphere>(center1, center2, 0, 1, 50, moving_sphere_material));

    objects.add(make_shared<sphere>(point3(260, 150, 45), 50, make_shared<dielectric>(1.5)));
    objects.add(make_shared<sphere>(
        point3(0, 150, 145), 50, make_shared<metal>(color(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = make_shared<sphere>(point3(360,150,145), 70, make_shared<dielectric>(1.5));
    objects.add(boundary);
    objects.add(make_shared<constant_medium>(boundary, 0.2, color(0.2, 0.4, 0.9)));
    boundary = make_shared<sphere>(point3(0, 0, 0), 5000, make_shared<dielectric>(1.5));
    objects.add(make_shared<constant_medium>(boundary, .0001, color(1,1,1)));

    auto emat = make_shared<lambertian>(make_shared<image_texture>("earthmap.jpg"));
    objects.add(make_shared<sphere>(point3(400,200,400), 100, emat));
    auto pertext = make_shared<noise_texture>(0.1);
    objects.add(make_shared<sphere>(point3(220,280,300), 80, make_shared<lambertian>(pertext)));

    hitable_list boxes2;
    auto white = make_shared<lambertian>(color(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(make_shared<sphere>(point3::random(0,165), 10, white));
    }

    objects.add(make_shared<translate>(
        make_shared<rotate_y>(
            make_shared<bvh_node>(boxes2, 0.0, 1.0), 15),
            vec3(-100,270,395)
        )
    );

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
    hitable_list world = final_scene();//Create a world containing the two objects.  You can use any other objects you like.
    color background(0,0,0);
    //camera
    vec3 lookfrom = point3(478, 278, -600);//相机位置
    vec3 lookat = point3(278, 278, 0);//相机目标点
    vec3 vup(0,1,0);//相机up向量
    auto vfov = 40.0;
    auto aspect_ratio = 1;
    float aperture = 0.0;//相机透镜光圈大小,越大越模糊
    float dist_to_focus = 10.0;//表示摄像机焦点到透镜的距离
    float exposure_time_start = 0.0;//曝光开始时间
    float exposure_time_end = 1.0;//曝光结束时间
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, exposure_time_start, exposure_time_end);
    //renderer
    int image_width = 800;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    const int max_depth = 50;//递归最大深度
    int samples_per_pixel = 10000;
    renderer ren(world,cam,image_width,image_height,samples_per_pixel,max_depth);
    ren.setBackground(color(0,0,0));
    ren.EnableBVH();
    ren.render(argv[1]);
    return 0;
}