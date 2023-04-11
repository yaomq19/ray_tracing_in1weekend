#include<iostream>
#include<vec3.h>
#include<sphere.h>
#include<hitable_list.h> 
#include<camera.h>
#include<renderer.h>
hitable* random_scene(int n)
{
    hitable** list = new hitable*[n+1];
    list[0] = new sphere(vec3(0,1000,0),1000,new lambertian(vec3(0.5,0.5,0.5)));
    int i = 1;
    for(int a = -11; a < 11; a++)
    {
        for(int b = -11; b < 11; b++)
        {   
            float choose_mat = drand48();
            vec3 center(a+0.9*drand48(), 0.2,b+0.9*drand48());
            if((center - vec3(4,0.2,0)).length() > 0.9){
                if(choose_mat < 0.8){
                    list[i++] = new sphere(center,0.2,new lambertian(vec3(drand48()*drand48(), drand48()*drand48(),drand48()*drand48())));
                }else if(choose_mat < 0.95){
                    list[i++] = new sphere(center,0.2,new metal(vec3(0.5*(1+drand48()),0.5*(1+drand48()),0.5*(1+drand48())),0.5+drand48()));
                }
                else {list[i++] = new sphere(center,0.2,new dielectric(1.5));}
            }
        }
    }
    list[i++] = new sphere(vec3(0, 1, 0), 1, new dielectric(1.5));
    list[i++] = new sphere(vec3(-4, 1, 0), 1, new lambertian(vec3(0.4,0.2, 0.1)));
    list[i++] = new sphere(vec3(4, 1, 0), 1, new metal(vec3(0.7, 0.6, 0.5), 0.0));
    return new hitable_list(list, i);;  //returning the hitable list of the objects to be hit by ray.intersects() method.
}
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    int rsl_hor = 200;//水平分辨率
    int rsl_ver =200;//垂直分辨率
    int msaa = 100;//MSAA采样频率
    
    // hitable *list[5];
    // list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
    // list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100,new lambertian(vec3(0.8,0.8,0.0)));
    // list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5,new metal(vec3(0.8,0.6,0.2),1.0));
    // list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5,new dielectric(1.5));
    // list[4] = new sphere(vec3(-1.0, 0.0, -1.0), -0.45,new dielectric(1.5));
    hitable *world = random_scene(500);//Create a world containing the two objects.  You can use any other objects you like.

    camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 45, (float)rsl_hor/rsl_ver, 0.1);
    renderer ren(world,cam,rsl_hor,rsl_ver,argv[1],msaa);
    ren.render();
    return 0;
}