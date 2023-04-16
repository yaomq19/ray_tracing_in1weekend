#include<iostream>
#include<fstream>
#include<myMath.h>


#include<vec3.h>
#include<ray.h>
#include<sphere.h>
#include<hitable_list.h> 
#include<camera.h>

#ifdef DEBUG
#include <windows.h>
#endif
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    }while(dot(p,p)>=1.0);
    return p;
}
vec3 color(const ray&r,hitable *world){
    hit_record rec; 	
    //如果与世界有击中记录则		
    if(world->hit(r,0.0,MAXFLOAT,rec)){
        //return unit_vector(rec.normal);
        return 0.5*vec3(rec.normal.x()+1,rec.normal.y()+1,rec.normal.z()+1);//The color is a shade from green to red.
    }
    //如果没有击中记录则用背景填充	
    else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);//Normalize the ray direction before we use it.  It will be used in the next step.
    }	//If the ray hits anything within the hitable list, it will rec
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

    hitable *list[2];
    list[0] = new sphere(vec3(0.0, 0.0, -1.0), 0.5);
    list[1] = new sphere(vec3(0.0, -100.5, -1), 100);
    
    
    hitable *world = new hitable_list(list,2);//Create a world containing the two objects.  You can use any other objects you like.

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
                
                col += color(r,world);
            }
            col /= float(ns);
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