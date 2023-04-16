#include<iostream>
#include<fstream>
//#include<drand48.h>
#include<myMath.h>

#include<vec3.h>
#include<ray.h>
#include<sphere.h>
#include<hitable_list.h> 
#include<camera.h>

#ifdef DEBUG
#include <windows.h>
#endif

//求r射线和world世界的相交颜色
vec3 color(const ray&r,hitable *world,int&& depth){
    hit_record rec; 	
    //如果与世界有击中记录则		
    if(world->hit(r,0.0,MAXFLOAT,rec)){
        ray scattered;
        vec3 attenuation;
        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation * color(scattered,world,depth+1);
        }else{
            return vec3(0,0,0);
        }
    }
    //如果没有击中记录则用背景填充	
    else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
    }
}
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    int nx = 200;
    int ny = 100;
    int ns = 100;//MSAA采样频率
    std::ofstream ofs(argv[1]);
    ofs<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0); //lower left corner of the image plane.  You can use
    vec3 horizontal(4.0, 0.0, 0.0); //any coordinate system you like.  The image plane is at z=0
    vec3 vertical(0.0, 2.0, 0.0); //vertical axis, you can use any coordinate system you like.
    vec3 origin(0.0,0.0,0.0);

    hitable *list[4];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5,new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0.0, -100.5, -1.0), 100,new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1.0, 0.0, -1.0), 0.5,new metal(vec3(0.8,0.6,0.2)));
    list[3] = new sphere(vec3(-1.0, 0.0, -1.0), 0.5,new metal(vec3(0.8,0.8,0.8)));
    
    hitable *world = new hitable_list(list,4);//Create a world containing the two objects.  You can use any other objects you like.

    camera cam;

    #ifdef DEBUG
    auto start = GetTickCount();
    #endif
    
    for(int j=ny-1;j>=0;j--)
    {
        for(int i=0;i<nx;i++)
        {
            vec3 col = vec3(0,0,0);
            for(int s=0;s<ns;s++){
                float u = float(i+drand48())/float(nx);
                float v = float(j+drand48())/float(ny);
                ray r = cam.get_ray(u,v);
                
                col += color(r,world,0);
            }
            col /= float(ns);
            //一种gamma校正
            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));

            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);
            ofs << ir << " " << ig << " " << ib << "\n"; //write it out to the file.  I used 255 for
        }
    }

    #ifdef DEBUG
    auto end = GetTickCount();
    #endif
    
    ofs.close();

    #ifdef DEBUG
    std::cout<<"run time = "<<end-start<<std::endl;
    #endif
}