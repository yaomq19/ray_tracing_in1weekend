#ifndef AABB_H
#define AABB_H
#include "vec3.h"
#include "ray.h"
class aabb {
    public:
        aabb() {}
        aabb(const vec3& a, const vec3& b) :minimum(a),maximum(b){}
        inline vec3 min() const {return minimum; }
        inline vec3 max() const {return maximum; }
        /*
            判断作用范围在[t_min,t_max]间的射线r是否与该boundingBox相交，
            若相交返回true，不相交返回false
            不需要返回交点，和包围盒的交点没有意义
        */
        inline bool hit(const ray& r, float t_min, float t_max) const {
            for (int a = 0; a < 3; a++) {
                auto invD = 1.0f / r.direction()[a];
                auto t0 = (min()[a] - r.origin()[a]) * invD;
                auto t1 = (max()[a] - r.origin()[a]) * invD;
                if (invD < 0.0f)
                    std::swap(t0, t1);
                t_min = t0 > t_min ? t0 : t_min;
                t_max = t1 < t_max ? t1 : t_max;
                if (t_max <= t_min)
                    return false;
            }
            return true;
        }
    private:
        vec3 minimum;//该boundingBox的最小点坐标
        vec3 maximum;//该boundingBox的最大点坐标
};
/*
    返回既包围box0又包围box1的大包围盒
*/
aabb surrounding_box(aabb box0, aabb box1);
#endif