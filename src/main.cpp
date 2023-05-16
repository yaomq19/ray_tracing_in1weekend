#include"rayTracing.h"
#include<iostream>
#include<fstream>
#include<time.h>
#include<thread>
#include<mutex>
#include<chrono>
#include<random>
using namespace std;
int main()
{
    camera cam(vec3(0, 0, 0), vec3(0, 0, -1), vec3(0, 1, 0), 90, 16.0 / 9.0, 0.1, 10);
    hitable_list world;
    renderer r(world, cam, 1920, 1080, 100, 50);
    r.EnableBVH();
    r.setBackground(color(0.5, 0.7, 1));
    r.render("fuck.ppm");
    return 0;
}