#ifndef HITABLELISTH
#define HITABLELISTH 
#include<memory>
#include<vector>
#include "aabb.h"
#include "hitable.h"
using namespace std;
class hitable_list:public hitable{
    public:
    //默认函数
    hitable_list(){}

    //有参构造
    hitable_list(std::shared_ptr<hitable> obj){add(obj);}

    //让作用域在[tmin,tmax]的射线r对objects中所有hitable进行命中检测，在rec处返回记录
    virtual bool hit(const ray& r,float tmin,float tmax, hit_record& rec) const override; 

    //
    virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

    void add(shared_ptr<hitable> ptr);

    vector<shared_ptr<hitable>> getObjects()const;
    private:
    vector<shared_ptr<hitable>> objects;
};

#endif