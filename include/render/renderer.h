#ifndef RENDERER_H
#define RENDERER_H
#include"camera.h"
#include<hitable.h>
#include<myMath.h>
#include<fstream>
#include <chrono>
#include "bvh.h"
#include "material.h"
#include "vec3.h"
#include <vector>
#include "external/thread_pool.h"
class renderer
{
public://接口
    //构造
    renderer(int rslu_hor,int rslu_ver,int msaa,int depth);
    //渲染至filename文件
    void render(char *filename);
    //设置渲染背景色为input
    void setBackground(color input);
    //开启BVH加速结构
    void EnableBVH();
    void setWorld(hitable_list* world);
    void setCamera(camera* cam);
private://成员变量
    bool isBvhEnable = false;//是否开启bvh加速
    int rslu_hor;//水平分辨率
    int rslu_ver;//竖直分辨率
    int msaa;//多重采样次数
    int m_depth;//渲染递归深度
    color background = color(0,0,0);//背景色
    camera* cam;//相机
    hitable_list* world;//需要渲染的世界
    bvh_node bvh;//需要渲染的世界封装成的BVH加速结构
    std::vector<int> buffer;//渲染缓冲区
private://私有函数
    //求r射线和world世界的相交颜色,范围[0,1]
    color ray_color(const ray&r,hitable_list* world,int&& depth);
    //求r射线和bvh世界的相交颜色,范围[0,1]
    color ray_color(const ray&r,bvh_node bvh,int&& depth);
};
#endif