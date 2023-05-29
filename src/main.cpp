#include<iostream>
#include<time.h>
#include<memory>
#include<fstream>
#include <string>
#include "rayTracing.h"
int main(int argc, char* argv[])
{
    if(argc!=2){
        std::cout<<"Usage : ./main <filename>"<<std::endl;
        exit(1);
    }
    srand(time(NULL));
    //world
    hitable_list world = Parser::parseHitableList("D:\\githubRepositories\\ray_tracing_in1weekend\\conf\\scene.xml");
    //camera
    camera cam = Parser::parseCamera("D:\\githubRepositories\\ray_tracing_in1weekend\\conf\\camera.xml");
    //renderer
    renderer ren = Parser::parseRenderer("D:\\githubRepositories\\ray_tracing_in1weekend\\conf\\renderer.xml");
    ren.setWorld(&world);
    ren.setCamera(&cam);
    ren.render(argv[1]);
    return 0;
}