#include "acceleration/bvh.h"
bvh_node::bvh_node(const hitable_list& list, float time0, float time1):bvh_node(list.getObjects(), 0, list.getObjects().size(), time0, time1){}
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
    bool hit_right = right->hit(r, t_min, hit_left ? rec.getTime() : t_max, rec);

    return hit_left || hit_right;
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