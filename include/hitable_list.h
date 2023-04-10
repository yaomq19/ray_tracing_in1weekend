#ifndef HITABLELISTH
#define HITABLELISTH 
class hitable_list:public hitable{
    public:
    hitable **list;//一个存有hitable*的一维列表
    int list_size;

    hitable_list(){}
    hitable_list(hitable **l,int n){list = l;list_size = n;} 
    //对所有hitable*进行测试，在返回值处返回是否有命中，并在rec处返回离屏幕最近的一个点的命中记录
    virtual bool hit(const ray& r,float tmin,float tmax, hit_record& rec) const; 
};
bool hitable_list::hit(const ray& r,float tmin,float tmax, hit_record& rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    for(int i=0;i<list_size;i++){
        //注意第三个参数为closest_so_far保证了只能取到比当前记录更近的记录
        if(list[i]->hit(r,tmin,closest_so_far,temp_rec)){
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