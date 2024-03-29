#include "hitable/hitable_list.h"
bool hitable_list::hit(const ray& r,float tmin,float tmax, hit_record& rec) const{
    hit_record temp_rec;
    bool hit_anything = false;
    float closest_so_far = tmax;
    for(int i=0;i<objects.size();i++){
        //注意第三个参数为closest_so_far保证了只能取到比当前记录更近的记录
        if(objects[i]->hit(r,tmin,closest_so_far,temp_rec)){
            hit_anything = true;
            //将最近值更新为最新测试通过的一个值
            closest_so_far = temp_rec.getTime();
            //更新为最近值
            rec = temp_rec;
        }
    }
    return hit_anything;
}
bool hitable_list::bounding_box(float time0, float time1, aabb& output_box) const {
    if (objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto& object : objects) {
        if (!object->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}
void hitable_list::add(shared_ptr<hitable> ptr){
    objects.push_back(ptr);
}
vector<shared_ptr<hitable>> hitable_list::getObjects()const{
    return objects;
}