#include<iostream>
#include<vec3.h>
#include<sphere.h>
#include<hitable_list.h> 
#include<camera.h>
#include<renderer.h>
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    int rsl_hor = 200;//水平分辨率
    int rsl_ver = 200;//垂直分辨率
    int msaa = 100;//MSAA采样频率
    
    hitable *list[5];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100,new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5,new metal(vec3(0.8,0.6,0.2),1.0));
    list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5,new dielectric(1.5));
    list[4] = new sphere(vec3(-1.0, 0.0, -1.0), -0.45,new dielectric(1.5));
    hitable *world = new hitable_list(list,5);//Create a world containing the two objects.  You can use any other objects you like.

    camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 45, (float)rsl_hor/rsl_ver, 0.1);
    renderer ren(world,cam,rsl_hor,rsl_ver,argv[1],msaa);
    ren.render();
    return 0;
}