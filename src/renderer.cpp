#include "renderer.h"
renderer::renderer(hitable_list world,const camera&cam,int rslu_hor,int rslu_ver,int msaa,int depth):world(world),cam(cam)
,m_depth(depth),bvh(world,0,1){
    this->rslu_hor=rslu_hor;
    this->rslu_ver=rslu_ver;
    this->msaa=msaa;
}
void renderer::render(char *filename)
{
    std::ofstream ofs(filename);
    ofs<<"P3\n"<<rslu_hor<<" "<<rslu_ver<<"\n255\n";
    auto start = std::chrono::steady_clock::now();
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
                if(isBvhEnable)
                    col += ray_color(r,bvh,0);
                else
                    col += ray_color(r,world,0);
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
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    std::cout << "Time elapsed: " << std::chrono::duration<double, std::milli>(diff).count() << " ms\n";
    ofs.close();
}
void renderer::EnableBVH(){
    isBvhEnable = true;
}
void renderer::setBackground(color input)
{
    this->background = input;
}
color renderer::ray_color(const ray&r,bvh_node bvh,int&& depth){
    hit_record rec; 
    //如果递归深度大于等于50返回背景色
    if(depth>=m_depth)return background;
    //如果与世界有击中记录则		
    if(bvh.hit(r,0.0,MAXFLOAT,rec)){
        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        //如果击中点rec的材质成功反射了光线
        if(rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            //attenuation为击中点材质的固有色
            return emitted + attenuation * ray_color(scattered,bvh,depth+1);
        else//没有击中说明这个hitable只是个纯光源
            return emitted;
        
    }
    //如果没有击中记录则用背景填充	
    else return background;
    // {
    //     vec3 unit_direction = unit_vector(r.direction());
    //     float t = 0.5 * (unit_direction.y() + 1.0);
    //     return (1.0-t)*vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
    // }
}
color renderer::ray_color(const ray&r,hitable_list world,int&& depth){
    hit_record rec; 
    //如果递归深度大于等于50返回背景色
    if(depth>=m_depth)return background;
    //如果与世界有击中记录则		
    if(world.hit(r,0.0,MAXFLOAT,rec)){
        ray scattered;
        color attenuation;
        color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        //如果击中点rec的材质成功反射了光线
        if(rec.mat_ptr->scatter(r,rec,attenuation,scattered))
            //attenuation为击中点材质的固有色
            return emitted + attenuation * ray_color(scattered,world,depth+1);
        else//没有击中说明这个hitable只是个纯光源
            return emitted;
        
    }
    //如果没有击中记录则用背景填充	
    else return background;
    // {
    //     vec3 unit_direction = unit_vector(r.direction());
    //     float t = 0.5 * (unit_direction.y() + 1.0);
    //     return (1.0-t)*vec3(1.0,1.0,1.0) + t * vec3(0.5,0.7,1.0);
    // }
}