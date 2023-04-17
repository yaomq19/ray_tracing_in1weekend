#ifndef VEC3H
#define VEC3H
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <random>
#include "myMath.h"
class vec3;
typedef vec3 point3;
typedef vec3 color;
class vec3{
    public:
    float e[3];
    vec3(){}
    vec3(float e0,float e1,float e2){e[0]=e0;e[1]=e1,e[2]=e2;}
    inline float x()const{return e[0];}
    inline float y()const{return e[1];}
    inline float z()const{return e[2];}
    inline float r()const{return e[0];}
    inline float g()const{return e[1];}
    inline float b()const{return e[2];}


    inline const vec3& operator+()const{return *this;}

    inline vec3 operator-()const{return vec3(-e[0],-e[1],-e[2]);}


    inline float operator[](int i)const{return e[i];}
    inline float& operator[](int i){return e[i];}
    inline vec3& operator+=(const vec3& v2){
        e[0]+=v2.e[0];
        e[1]+=v2.e[1];
        e[2]+=v2.e[2];
        return *this;
    }
    inline vec3& operator-=(const vec3& v2){
        e[0]-=v2.e[0];
        e[1]-=v2.e[1];
        e[2]-=v2.e[2];
        return *this;
    }
    inline vec3& operator*=(const vec3& v2){
        e[0]*=v2.e[0];
        e[1]*=v2.e[1];
        e[2]*=v2.e[2];
        return *this;
    }
    inline vec3& operator/=(const vec3& v2){
        e[0]/=v2.e[0];
        e[1]/=v2.e[1];
        e[2]/=v2.e[2];
        return *this;
    }

    inline vec3& operator*=(const float t){e[0] *= t;e[1] *= t;e[2] *= t;return *this;}
    inline vec3& operator/=(const float t){e[0] /= t;e[1] /= t;e[2] /= t;return *this;}

    inline vec3 operator*(const float t)const
    {  
        return vec3(this->e[0] * t,this->e[1] * t,this->e[2] * t);
    }
    inline vec3 operator/(const float t)const
    {
        return vec3(this->e[0] / t,this->e[1] / t,this->e[2] / t);
    }
    inline vec3& operator=(const vec3& other){
        this->e[0] = other.e[0]; 
        this->e[1] = other.e[1]; 
        this->e[2] = other.e[2];
        return *this;
    }
    inline float length()const{return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
    inline float squared_length()const{return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    inline float length_squared()const{return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    inline vec3& normalize(){*this/=length(); 
        return *this;};
    inline vec3 normalized()const{
        return *this / length();
    }
    inline bool near_zero()const
    {
        const auto s = 1e-8; // 定义一个很小的常量
        return (fabs(x()) < s) && (fabs(y()) < s) && (fabs(z()) < s);
    }
    static vec3 random(float min,float max){
        return vec3(random_float(min,max),random_float(min,max),random_float(min,max));
    }
    void print()
    {
        std::cout<<e[0]<<" "<<e[1]<<" "<<e[2]<<std::endl;
    }
};

inline vec3 operator+(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);}
inline vec3 operator-(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);}
inline vec3 operator*(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);}
inline vec3 operator/(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]);}
inline vec3 operator*(const float t,const vec3 &v2)
{  
    return  vec3(v2.e[0]*t,v2.e[1]*t,v2.e[2]*t);
}
inline float dot(const vec3 &v1,const vec3 &v2){return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];}
inline vec3 cross(const vec3 &v1,const vec3 &v2){
        return vec3(
            (v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
            (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
            (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
            );
        }
inline vec3 unit_vector(vec3 v){
    if(v.length() > 0)
        return v/v.length();
    else return vec3(0,0,0);
}






#endif