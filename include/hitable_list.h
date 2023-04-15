#ifndef HITABLELISTH
#define HITABLELISTH 
#include<memory>
#include<vector>
using namespace std;
class hitable_list:public hitable{
    public:
    vector<shared_ptr<hitable>> list;

    hitable_list(){}
    //对所有hitable*进行测试，在返回值处返回是否有命中，并在rec处返回离屏幕最近的一个点的命中记录
    virtual bool hit(const ray& r,float tmin,float tmax, hit_record& rec) const; 
    void add(shared_ptr<hitable> ptr){
        list.push_back(ptr);
    }
};
bool hitable_list::hit(const ray& r,float tmin,float tmax, hit_record& rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    for(const auto & it:list){
        //注意第三个参数为closest_so_far保证了只能取到比当前记录更近的记录
        if(it->hit(r,tmin,closest_so_far,temp_rec)){
            hit_anything = true;
            //将最近值更新为最新测试通过的一个值
            closest_so_far = temp_rec.t;
            //更新为最近值
            rec = temp_rec;
        }
    }
    return hit_anything;
}
#endif