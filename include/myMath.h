#ifndef MYMATH_H
#define MYMATH_H
#include <stdlib.h>
#include <math.h>
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


#endif
