#ifndef AABB_H
#define AABB_H
#include "vec3.h"
class aabb {
    public:
        aabb() {}
        aabb(const vec3& a, const vec3& b) { minimum = a; maximum = b;}
        vec3 min() const {return minimum; }
        vec3 max() const {return maximum; }
        //判断作用范围在[t_min,t_max]间的射线r是否与该boundingBox相交，若相交返回true，不相交返回false
        inline bool hit(const ray& r, float t_min, float t_max) const;
        vec3 minimum;//该boundingBox的最小点坐标
        vec3 maximum;//该boundingBox的最大点坐标
};

inline bool aabb::hit(const ray& r, float t_min, float t_max) const {
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

#endif