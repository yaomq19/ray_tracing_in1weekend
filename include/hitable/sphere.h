#ifndef SPHEREH
#define SPHEREH
#include <hitable.h>
#include <memory>
using namespace std;

class sphere:public hitable{
    public:
    sphere();
    sphere(vec3 cen,float r,shared_ptr<material> m);
    //抽象方法hitable::hit的重写，具体实现了该方法
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const;
    virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

    private:
    vec3 center;//球体中心坐标
    float radius;//球体半径
    shared_ptr<material> mat_ptr;
    static void get_sphere_uv(const point3& p, float& u, float& v);
};

#endif