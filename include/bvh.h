#ifndef BVH_H
#define BVH_H
#include <algorithm>
#include "hitable.h"
#include "hitable_list.h"
class bvh_node : public hitable {
    public:
        bvh_node(){}
        bvh_node(const hitable_list& list, float time0, float time1)
            : bvh_node(list.getObjects(), 0, list.getObjects().size(), time0, time1){}//[0,size())左闭右开
        bvh_node(const std::vector<shared_ptr<hitable>>& src_objects,
            size_t start, size_t end, float time0, float time1);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
        static inline bool box_compare(const shared_ptr<hitable> a, const shared_ptr<hitable> b, int axis);
        static bool box_x_compare (shared_ptr<hitable> a, shared_ptr<hitable> b);
        static bool box_y_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b);
        static bool box_z_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b);
    public:
        shared_ptr<hitable> left;
        shared_ptr<hitable> right;
        aabb box;
};


bvh_node::bvh_node(const std::vector<shared_ptr<hitable>>& src_objects,
    size_t start, size_t end, float time0, float time1) {
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = random_int(0,2);
    auto comparator = box_x_compare;
    if(axis == 0){
        comparator = box_x_compare;
    }else if(axis == 1){
        comparator = box_y_compare;
    }else{
        comparator = box_z_compare;
    }
    //object_span：obj的个数
    size_t object_span = end - start;
    if (object_span == 1) {
        left = right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left = objects[start];
            right = objects[start+1];
        } else {
            left = objects[start+1];
            right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_left, box_right;

    if (  !left->bounding_box (time0, time1, box_left)
       || !right->bounding_box(time0, time1, box_right)
    )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    box = surrounding_box(box_left, box_right);
}
bool bvh_node::bounding_box(float time0, float time1, aabb& output_box) const {
    output_box = box;
    return true;
}
bool bvh_node::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
    if (!box.hit(r, t_min, t_max))
        return false;

    bool hit_left = left->hit(r, t_min, t_max, rec);
    bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}
inline bool bvh_node::box_compare(const shared_ptr<hitable> a, const shared_ptr<hitable> b, int axis) {
    aabb box_a;
    aabb box_b;
    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";
    //如果box_a的最小点的x坐标小于box_b的返回真
    return box_a.min().e[axis] < box_b.min().e[axis];
}
bool bvh_node::box_x_compare (shared_ptr<hitable> a, shared_ptr<hitable> b) {
    return box_compare(a, b, 0);
}
bool bvh_node::box_y_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b) {
    return box_compare(a, b, 1);
}
bool bvh_node::box_z_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b) {
    return box_compare(a, b, 2);
}
#endif