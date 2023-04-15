#include<iostream>
#include"material.h"
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
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 100;
    const int max_depth = 50;//递归最大深度
    float dist_to_focus = 10.0;//表示摄像机焦点到透镜的距离
    float aperture = 0.1;//透镜光圈大小
    int image_height = static_cast<int>(image_width / aspect_ratio);

    srand(time(NULL));

    hitable_list world = random_scene();//Create a world containing the two objects.  You can use any other objects you like.

    
    vec3 lookfrom(13,2,3);//相机位置
    vec3 lookat(0,0,0);//相机目标点
    vec3 vup(0,1,0);//相机up向量
    

    //快门时间设置到0至1秒内
    camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);
    renderer ren(world,cam,image_width,image_height,argv[1],samples_per_pixel);
    ren.render();
    return 0;
}