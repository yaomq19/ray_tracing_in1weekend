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
hitable_list transform(){
    hitable_list world;
    shared_ptr<material> red   = make_shared<lambertian>(color(0.65, 0.05, 0.05));
    shared_ptr<material> green   = make_shared<lambertian>(color(0.00, 0.75, 0.55));
    shared_ptr<material> light = make_shared<diffuse_light>(color(3, 3, 3));

    
    //棋盘纹理
    std::shared_ptr<texture>checker_tex = make_shared<checker_texture>(color(1,1,1),color(0.0,0.6,0.5),1);
    //使用棋盘纹理的漫反射材质
    std::shared_ptr<material>diff_checker_mat = make_shared<lambertian>(checker_tex);
    
    //红色金属材质
    std::shared_ptr<material>gray_metal_mat = make_shared<metal>(color(0.95,0.2,0.2),1.0);  
    
    float brightness = 4.0;
    //高亮纯白色纹理
    std::shared_ptr<texture> solid_color_tex = make_shared<solid_color>(brightness,brightness,brightness);
    //使用高亮纯白色纹理的漫反射材质
    std::shared_ptr<material>diff_light_mat = make_shared<lambertian>(solid_color_tex);
    
    //纯蓝色纹理
    std::shared_ptr<texture> blue = make_shared<solid_color>(0.2,0.2,1.0);
    //使用纯蓝色纹理的漫反射材质
    std::shared_ptr<material>blue_metal_mat = make_shared<lambertian>(blue);

    //
    float zv = 0.04;
    float radius = 22.73;
    //使用（使用棋盘纹理的漫反射材质）的小球
    shared_ptr<hitable> sp = make_shared<sphere>(point3(-0.453,0,40.199),radius,diff_checker_mat);
    world.add(sp);
    world.add(make_shared<translate>(sp,vec3(50,0,0)));
    //使用（红色金属材质）的小球
    world.add(make_shared<sphere>(point3(-54.0,0.0,-40.812),radius,gray_metal_mat));
    //使用（蓝色漫反射材质）的小球
    world.add(make_shared<sphere>(point3(52.918,0,-42.501),radius,blue_metal_mat));

    float radius2 = 10000000000000000000000000.0;
    //三个泛光
    world.add(make_shared<sphere>(point3(29.584,251.259,0.0),radius2,diff_light_mat));
    world.add(make_shared<sphere>(point3(-244.573,-115.033,0.0),radius2,diff_light_mat));
    world.add(make_shared<sphere>(point3(240.82,-186.943,0.0),radius2,diff_light_mat));
    return world;
}
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    srand(time(NULL));
    //world
    hitable_list world = transform();//Create a world containing the two objects.  You can use any other objects you like.
    color background(0,0,0);

    //camera
    vec3 lookfrom(-4.788,-179.111,0.739);//相机位置
    vec3 lookat(0.267,136.331,-0.477);//相机目标点
    vec3 vup(1,0,0);//相机up向量
    auto vfov = 91;
    auto aspect_ratio = 1;
    float aperture = 0.0;//相机透镜光圈大小,越大越模糊
    float dist_to_focus = 10.0;//表示摄像机焦点到透镜的距离
    float exposure_time_start = 0.0;//曝光开始时间
    float exposure_time_end = 1.0;//曝光结束时间
    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, exposure_time_start, exposure_time_end);
    //renderer
    int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    const int max_depth = 50;//递归最大深度
    int samples_per_pixel = 100;
    renderer ren(world,cam,image_width,image_height,samples_per_pixel,max_depth);
    ren.setBackground(color(0.2,0.2,0.2));
    //ren.EnableBVH();
    ren.render(argv[1]);
    return 0;
}