#ifndef PARSEH
#define PARSEH
#include <fstream>
#include "camera.h"
#include "renderer.h"
#include "hitable_list.h"
class Parser
{
public:
    static camera parseCamera(std::string filename);
    static renderer parseRenderer(std::string filename);
    static hitable_list parseHitableList(std::string filename);
};
#endif