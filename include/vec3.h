#pragma once
#include <math.h>
#include <stdlib.h>
#include <iostream>
class vec3{
    public:
    vec3(){}
    vec3(float e0,float e1,float e2){e[0]=e0;e[1]=e1,e[2]=e2;}
    inline float x()const{return e[0];}
    inline float y()const{return e[1];}
    inline float z()const{return e[2];}
    inline float r()const{return e[0];}
    inline float g()const{return e[1];}
    inline float b()const{return e[2];}

    //用常引用是为了节省空间
    inline const vec3& operator+()const{return *this;}
    //取负值则必须新构造一个vec3，返回匿名的新对象不需要加const，因为不会修改本对象的e数组
    inline vec3 operator-()const{return vec3(-e[0],-e[1],-e[2]);}

    //常对象不允许修改值，非常对象允许修改值
    inline float operator[](int i)const{return e[i];}
    inline float& operator[](int i){return e[i];}

    inline vec3& operator+=(const vec3& v2);
    inline vec3& operator-=(const vec3& v2);
    inline vec3& operator*=(const vec3& v2);
    inline vec3& operator/=(const vec3& v2);

    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline vec3 operator*(const float t)
    {  
        return vec3(this->e[0] * t,this->e[1] * t,this->e[2] * t);
    }
    inline vec3 operator/(const float t)
    {
        return vec3(this->e[0] / t,this->e[1] / t,this->e[2] / t);
    }

    inline float length()const{return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
    inline float squared_length()const{return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
    inline void make_unit_vector();

    
    float e[3];
};

inline vec3 operator+(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]+v2.e[0],v1.e[1]+v2.e[1],v1.e[2]+v2.e[2]);}
inline vec3 operator-(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]-v2.e[0],v1.e[1]-v2.e[1],v1.e[2]-v2.e[2]);}
inline vec3 operator*(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);}
inline vec3 operator/(const vec3 &v1,const vec3 &v2){return vec3(v1.e[0]/v2.e[0],v1.e[1]/v2.e[1],v1.e[2]/v2.e[2]);}

inline float dot(const vec3 &v1,const vec3 &v2){return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];}
inline vec3 cross(const vec3 &v1,const vec3 &v2){
        return vec3(
            (v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
            (-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
            (v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
            );
        }
    
inline vec3 unit_vector(vec3 v){return v/v.length();}