#ifndef MYMATH_H
#define MYMATH_H

#include <stdlib.h>
#include <vec3.h>
#define MAXFLOAT 3.402823E38
static unsigned long long seed = 1;

//生成一个均匀分布与[0,1]的double随机数
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

//返回一个由一个虚拟单位球的球心到该球体内任意一点（不超过球体边界）的长度方向向量
vec3 random_in_unit_sphere(){
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(),drand48(),drand48()) - vec3(1,1,1);
    }while(dot(p,p)>=1.0);
    return p;
}
#endif
