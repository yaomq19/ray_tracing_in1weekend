#ifndef VEC3H
#define VEC3H
#include <stdlib.h>
#include <math.h>
#include <iostream>

class vec3{
    public:
    float e[3];
    vec3();
    vec3(float e0,float e1,float e2);
    inline float x()const;
    inline float y()const;
    inline float z()const;
    inline float r()const;
    inline float g()const;
    inline float b()const;
    inline const vec3& operator+()const;
    inline vec3 operator-()const;
    inline float operator[](int i)const;
    inline float& operator[](int i);
    inline vec3& operator+=(const vec3& v2);
    inline vec3& operator-=(const vec3& v2);
    inline vec3& operator*=(const vec3& v2);
    inline vec3& operator/=(const vec3& v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);
    inline vec3 operator*(const float t)const;
    inline vec3 operator/(const float t)const;
    inline vec3& operator=(const vec3& other);
    inline float length()const;
    inline float squared_length()const;
    inline float length_squared()const;
    inline vec3& normalize();
    inline vec3 normalized()const;
    inline bool near_zero()const;
    static vec3 random(float min,float max);
    void print();
};
typedef vec3 point3;
typedef vec3 color;
inline vec3 operator+(const vec3 &v1,const vec3 &v2);
inline vec3 operator-(const vec3 &v1,const vec3 &v2);
inline vec3 operator*(const vec3 &v1,const vec3 &v2);
inline vec3 operator/(const vec3 &v1,const vec3 &v2);
inline vec3 operator*(const float t,const vec3 &v2);
inline float dot(const vec3 &v1,const vec3 &v2);
inline vec3 cross(const vec3 &v1,const vec3 &v2);
inline vec3 unit_vector(vec3 v);



vec3::vec3(){}
vec3::vec3(float e0,float e1,float e2){e[0]=e0;e[1]=e1,e[2]=e2;}
inline float vec3::x()const{return e[0];}
inline float vec3::y()const{return e[1];}
inline float vec3::z()const{return e[2];}
inline float vec3::r()const{return e[0];}
inline float vec3::g()const{return e[1];}
inline float vec3::b()const{return e[2];}


inline const vec3& vec3::operator+()const{return *this;}

inline vec3 vec3::operator-()const{return vec3(-e[0],-e[1],-e[2]);}


inline float vec3::operator[](int i)const{return e[i];}
inline float& vec3::operator[](int i){return e[i];}
inline vec3& vec3::operator+=(const vec3& v2){
    e[0]+=v2.e[0];
    e[1]+=v2.e[1];
    e[2]+=v2.e[2];
    return *this;
}
inline vec3& vec3::operator-=(const vec3& v2){
    e[0]-=v2.e[0];
    e[1]-=v2.e[1];
    e[2]-=v2.e[2];
    return *this;
}
inline vec3& vec3::operator*=(const vec3& v2){
    e[0]*=v2.e[0];
    e[1]*=v2.e[1];
    e[2]*=v2.e[2];
    return *this;
}
inline vec3& vec3::operator/=(const vec3& v2){
    e[0]/=v2.e[0];
    e[1]/=v2.e[1];
    e[2]/=v2.e[2];
    return *this;
}

inline vec3& vec3::operator*=(const float t){e[0] *= t;e[1] *= t;e[2] *= t;return *this;}
inline vec3& vec3::operator/=(const float t){e[0] /= t;e[1] /= t;e[2] /= t;return *this;}

inline vec3 vec3::operator*(const float t)const
{  
    return vec3(this->e[0] * t,this->e[1] * t,this->e[2] * t);
}
inline vec3 vec3::operator/(const float t)const
{
    return vec3(this->e[0] / t,this->e[1] / t,this->e[2] / t);
}
inline vec3& vec3::operator=(const vec3& other){
    this->e[0] = other.e[0]; 
    this->e[1] = other.e[1]; 
    this->e[2] = other.e[2];
    return *this;
}
inline float vec3::length()const{return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
inline float vec3::squared_length()const{return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
inline float vec3::length_squared()const{return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];}
inline vec3& vec3::normalize(){*this/=length(); 
    return *this;};
inline vec3 vec3::normalized()const{
    return *this / length();
}
inline bool vec3::near_zero()const
{
    const auto s = 1e-8; // 定义一个很小的常量
    return (fabs(x()) < s) && (fabs(y()) < s) && (fabs(z()) < s);
}
vec3 vec3::random(float min,float max){
    float a = ((float)(rand()%10000)/5000.f) - 1.0;
    float b = ((float)(rand()%10000)/5000.f) - 1.0;
    float c = ((float)(rand()%10000)/5000.f) - 1.0;
    return vec3(a,b,c);
}
void vec3::print()
{
    std::cout<<e[0]<<" "<<e[1]<<" "<<e[2]<<std::endl;
}

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