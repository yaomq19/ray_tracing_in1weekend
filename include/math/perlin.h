#ifndef PERLIN_H
#define PERLIN_H

#include "vec3.h"
#include "myMath.h"
class perlin {
    public:
        perlin();
        ~perlin();
        float noise(const point3 & p)const;
        float turb(const point3& p, int depth=7)const;
    private:
        static const int point_count = 256;
        vec3* ranvec;
        int* perm_x;
        int* perm_y;
        int* perm_z;
        static int* perlin_generate_perm();
        static void permute(int* p, int n);
        static float perlin_interp(vec3 c[2][2][2], float u, float v, float w);
};



#endif