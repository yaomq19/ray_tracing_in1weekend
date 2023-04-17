#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H
#include "hitable.h"
#include "material.h"
#include "texture.h"

class constant_medium : public hitable {
    public:
        constant_medium(shared_ptr<hitable> b, float d, shared_ptr<texture> a)
            : boundary(b),
              neg_inv_density(-1/d),
              phase_function(make_shared<isotropic>(a))
            {}
        constant_medium(shared_ptr<hitable> b, float d, color c)
            : boundary(b),
              neg_inv_density(-1/d),
              phase_function(make_shared<isotropic>(c))
            {}
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        virtual bool bounding_box(float time0, float time1, aabb& output_box) const;

    private:
        shared_ptr<hitable> boundary;
        shared_ptr<material> phase_function;
        float neg_inv_density;
};
#endif