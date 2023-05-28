#include "parse.h"
#include "all.h"
#include <string>
camera Parser::parseCamera(std::string filename){
    ifstream ifs(filename);
    if(!ifs.is_open()){
        std::cout<<"Error : Cannot open file "<<filename<<std::endl;
        exit(1);
    }
    vec3 pos,target,up;
    float vfov,aspect_ratio,aperture,focus_dist;
    float exposure_time_start,exposure_time_end;
    std::string attr; 
    while(!ifs.eof()){
        ifs>>attr;
        if(attr == "pos"){
            ifs>>pos[0]>>pos[1]>>pos[2];
        }else if(attr == "target"){
            ifs>>target[0]>>target[1]>>target[2];
        }else if(attr == "up"){
            ifs>>up[0]>>up[1]>>up[2];
        }else if(attr == "vfov"){
            ifs>>vfov;
        }else if(attr == "aspect_ratio"){
            ifs>>aspect_ratio;
        }else if(attr == "aperture"){
            ifs>>aperture;
        }else if(attr == "focus_dist"){
            ifs>>focus_dist;
        }else if(attr == "exposure_time_start"){
            ifs>>exposure_time_start;
        }else if(attr == "exposure_time_end"){
            ifs>>exposure_time_end;
        }else{
            std::cout<<"Error : Unknown attribute "<<attr<<std::endl;
            exit(1);
        }
    }
    ifs.close();
    return camera(pos,target,up,vfov,aspect_ratio,aperture,focus_dist,exposure_time_start,exposure_time_end);
}
renderer Parser::parseRenderer(std::string filename){
    ifstream ifs(filename);
    if(!ifs.is_open()){
        std::cout<<"Error : Cannot open file "<<filename<<std::endl;
        exit(1);
    }
    int image_width,image_height,samples_per_pixel,max_depth;
    vec3 background_color;
    std::string attr;
    while(!ifs.eof()){
        ifs>>attr;
        if(attr == "image_width"){
            ifs>>image_width;
        }else if(attr == "image_height"){
            ifs>>image_height;
        }else if(attr == "samples_per_pixel"){
            ifs>>samples_per_pixel;
        }else if(attr == "max_depth"){
            ifs>>max_depth;
        }else if(attr == "background_color"){
            ifs>>background_color[0]>>background_color[1]>>background_color[2];
        }
        else{
            std::cout<<"Error : Unknown attribute "<<attr<<std::endl;
            exit(1);
        }
    }
    ifs.close();
    renderer res(image_width,image_height,samples_per_pixel,max_depth);
    if(background_color.length() != 0){
        res.setBackground(background_color);
    }
    return res;
}
hitable_list Parser::parseHitableList(std::string filename){
    hitable_list res;
    ifstream ifs(filename);
    if(!ifs.is_open()){
        std::cout<<"Error : Cannot open file "<<filename<<std::endl;
        exit(1);
    }
    std::string attr;
    std::vector<shared_ptr<material>> materials;
    while(!ifs.eof()){
        ifs>>attr;
        if(attr=="materialNum"){
            int materialNum;
            ifs>>materialNum;
            for(int i=0;i<materialNum;i++){
                int matId;
                std::string matType;
                ifs>>matId>>matType;
                if(matType=="lambertian"){
                    color albedo;
                    ifs>>albedo[0]>>albedo[1]>>albedo[2];
                    materials.push_back(make_shared<lambertian>(albedo));
                }
                else if(matType=="metal"){
                    color albedo;
                    float fuzz;
                    ifs>>albedo[0]>>albedo[1]>>albedo[2]>>fuzz;
                    materials.push_back(make_shared<metal>(albedo,fuzz));
                }
                else if(matType=="dielectric"){
                    float ref_idx;
                    ifs>>ref_idx;
                    materials.push_back(make_shared<dielectric>(ref_idx));
                }
                else if(matType=="diffuse_light"){
                    color emit;
                    ifs>>emit[0]>>emit[1]>>emit[2];
                    materials.push_back(make_shared<diffuse_light>(emit));
                }
                else{
                    std::cout<<"Error : Unknown material type "<<matType<<std::endl;
                    exit(1);
                }
            }
        }
        else if(attr=="hitableNum"){
            int hitableNum;
            ifs>>hitableNum;
            for(int i=0;i<hitableNum;i++){
                ifs>>attr;
                if(attr=="sphere"){
                    point3 center;
                    float radius;
                    int matId;
                    ifs>>center[0]>>center[1]>>center[2]>>radius>>matId;
                    shared_ptr<hitable> sp = make_shared<sphere>(center,radius,materials[matId]);
                    res.add(sp);
                }
            }
        }
    }
    return res;
}