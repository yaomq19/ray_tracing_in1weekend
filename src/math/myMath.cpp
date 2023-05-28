#include "myMath.h"
#include <random>
#include "vec3.h"
static unsigned long long seed = 1;
double drand48(void)
{
	seed = (0x5DEECE66DLL * seed + 0xB16) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
    return 	((double)x / (double)0x100000000LL);
}

void srand48(unsigned int i)
{
    seed  = (((long long int)i) << 16) | rand();
}
vec3 random_in_unit_disk()
{
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(),drand48(),0) - vec3(1,1,0);
    }while(dot(p,p)>=1.0);
    return p;
}
float random_float(float min, float max) {
    return rand() / (double)RAND_MAX *(max - min) + min;
}
int random_int(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(random_float(min, max+1));
}
//返回一个由一个虚拟单位球的球心到该球体内任意一点（不超过球体边界）的长度方向向量
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    }while(dot(p,p)>=1.0);
    return p;
}
//返回一个每一项都在[0,1]之间的向量
vec3 random_vec3_0to1(){
    return vec3(random_float(0.0,1.0),random_float(0.0,1.0),random_float(0.0,1.0));
}
