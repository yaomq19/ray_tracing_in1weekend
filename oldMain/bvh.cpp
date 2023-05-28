#include<iostream>
#include"material.h"
#include "bvh.h"
#include<vec3.h>
#include<sphere.h>
#include<hitable_list.h> 
#include<movingSphere.h>
#include<camera.h>
#include<renderer.h>
#include<time.h>
#include<memory>
hitable_list random_scene()
{
    hitable_list world;
    //一个指向一种棋盘纹理材质的指针
    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));
    world.add(make_shared<sphere>(point3(0,-1000,0), 1000, make_shared<lambertian>(checker)));
    
    
    for(int a = -11; a < 11; a++)
    {
        for(int b = -11; b < 11; b++)
        {   
            float choose_mat = drand48();
            //随机生成一个球心
            vec3 center(a+0.9*drand48(), 0.2,b+0.9*drand48());
            //只有满足这个条件才生成球体
            if((center - vec3(4,0.2,0)).length() > 0.9){
                shared_ptr<material> sphere_material;
                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = random_vec3() * random_vec3();
                    sphere_material = make_shared<lambertian>(albedo);
                    auto center2 = center + vec3(0, random_float(0,.5), 0);
                    world.add(make_shared<moving_sphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = random_vec3();
                    auto fuzz = random_float(0, 0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<lambertian>(vec3(0.4, 0.2, 0.1));
    world.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<metal>(vec3(0.7, 0.6, 0.5), 0.0);
    world.add(make_shared<sphere>(vec3(4, 1, 0), 1.0, material3));

    return world;
}
hitable_list two_spheres(){
    hitable_list objects;

    auto checker = make_shared<checker_texture>(color(0.2, 0.3, 0.1), color(0.9, 0.9, 0.9));

    objects.add(make_shared<sphere>(point3(0,-10, 0), 10, make_shared<lambertian>(checker)));
    objects.add(make_shared<sphere>(point3(0, 10, 0), 10, make_shared<lambertian>(checker)));

    return objects;
}
hitable_list earth() {
    auto earth_texture = make_shared<image_texture>("../resource/earthmap.jpg");
    auto earth_surface = make_shared<lambertian>(earth_texture);
    auto globe = make_shared<sphere>(point3(0,0,0), 2, earth_surface);

    return hitable_list(globe);
}
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    srand(time(NULL));

    float aperture;//相机透镜光圈大小,越大越模糊
    //world
    
    hitable_list world = random_scene();//Create a world containing the two objects.  You can use any other objects you like.
    
    switch (0) {
        default:
        case 1:
            world = random_scene();
            aperture = 0.1;
            break;
        case 2:
            world = two_spheres();
            aperture=0.5;
            break;
        
        case 4:
            world = earth();
            break;
    }

    //camera
    vec3 lookfrom(13,2,3);//相机位置
    vec3 lookat(0,0,0);//相机目标点
    vec3 vup(0,1,0);//相机up向量
    auto vfov = 40.0;
    auto aspect_ratio = 16.0 / 9.0;
    float dist_to_focus = 10.0;//表示摄像机焦点到透镜的距离
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    
    //renderer
    int image_width = 400;
    int image_height = static_cast<int>(image_width / aspect_ratio);
    const int max_depth = 50;//递归最大深度
    int samples_per_pixel = 100;
    renderer ren(world,cam,image_width,image_height,samples_per_pixel,max_depth);
    ren.EnableBVH();
    ren.render(argv[1]);
    return 0;
}