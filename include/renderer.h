#ifndef RENDERER_H
#define RENDERER_H
#include<camera.h>
#include<hitable.h>
#include<myMath.h>
#include<fstream>
#ifdef DEBUG
#include <windows.h>
#endif
class renderer
{
    public:
    camera cam;
    int rslu_hor;
    int rslu_ver;
    int msaa;

    hitable_list world;
    char *filename;
    public:
    renderer(hitable_list world,const camera&cam,int rslu_hor,int rslu_ver,char *filename,int msaa=4):world(world),cam(cam)
    {
        this->rslu_hor=rslu_hor;
        this->rslu_ver=rslu_ver;
        this->msaa=msaa;
        this->filename=filename;
    }
    void render()
    {
        std::ofstream ofs(filename);
        ofs<<"P3\n"<<rslu_hor<<" "<<rslu_ver<<"\n255\n";
        for(int j=rslu_ver-1;j>=0;j--)
        {
            std::cout<<j<<" of "<<rslu_ver<<std::endl;
            for(int i=0;i<rslu_hor;i++)
            {
                vec3 col = vec3(0,0,0);
                for(int s=0;s<msaa;s++){
                    float u = float(i+drand48())/float(rslu_hor);
                    float v = float(j+drand48())/float(rslu_ver);
                    ray r = cam.get_ray(u,v);
                    col += color(r,world,0);
                }
                //col取值范围[0,1],[0,1],[0,1]
                col /= float(msaa);
                //一种gamma校正
                col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
                int ir = int(255.99*col[0]);
                int ig = int(255.99*col[1]);
                int ib = int(255.99*col[2]);
                ofs << ir << " " << ig << " " << ib << "\n"; //write it out to the file.  I used 255 for
            }
        }
        ofs.close();
    }
    private:
    //求r射线和world世界的相交颜色,范围[0,1]
    vec3 color(const ray&r,hitable_list world,int&& depth){
        hit_record rec; 	
        //如果与世界有击中记录则		
        if(world.hit(r,0.0,MAXFLOAT,rec)){
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

};
#endif