#ifndef MYMATH_H
#define MYMATH_H
#include <stdlib.h>
#include <math.h>
class vec3;
#define MAXFLOAT (3.402823E38)
//生成一个均匀分布与[0,1]的double随机数
double drand48(void);
void srand48(unsigned int i);
vec3 random_in_unit_disk();
float random_float(float t0 = 0.0,float t1 = 0.1);
int random_int(int min, int max);
//返回一个由一个虚拟单位球的球心到该球体内任意一点（不超过球体边界）的长度方向向量
vec3 random_in_unit_sphere();
//返回一个每一项都在[0,1]之间的向量
vec3 random_vec3();
inline float degrees_to_radians(float angle){
    float radians = angle * 3.14159265358979323846f / 180.0f; 
    return radians;
}

#endif
