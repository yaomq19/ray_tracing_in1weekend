#ifndef BOX_H
#define BOX_H
#include "axis_aligned_rect.h"
#include "hitable_list.h"

class box : public hitable  {
    public:
        box() {}
        box(const point3& p0, const point3& p1, shared_ptr<material> ptr);
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

    private:
        point3 box_min;//最小点
        point3 box_max;//最大点
        hitable_list sides;//面
};


#endif