#ifndef BVH_H
#define BVH_H
#include <algorithm>
#include "hitable.h"
#include "hitable_list.h"
class bvh_node : public hitable {
    public:
        bvh_node(){}
        bvh_node(const hitable_list& list, float time0, float time1);
        bvh_node(const std::vector<shared_ptr<hitable>>& src_objects,size_t start, size_t end, float time0, float time1);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;
        static inline bool box_compare(const shared_ptr<hitable> a, const shared_ptr<hitable> b, int axis) {
            aabb box_a;
            aabb box_b;
            if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
                std::cerr << "No bounding box in bvh_node constructor.\n";
            //如果box_a的最小点的x坐标小于box_b的返回真
            return box_a.min().e[axis] < box_b.min().e[axis];
        }
        static bool box_x_compare (shared_ptr<hitable> a, shared_ptr<hitable> b);
        static bool box_y_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b);
        static bool box_z_compare (const shared_ptr<hitable> a, const shared_ptr<hitable> b);
    public:
        shared_ptr<hitable> left;
        shared_ptr<hitable> right;
        aabb box;
};



#endif