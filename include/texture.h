#ifndef TEXTURE_H
#define TEXTURE_H

#include "vec3.h"
#include "perlin.h"
#include <memory>
using namespace std;
class texture {
    public:
        virtual color value(float u, float v, const vec3& p) const = 0;
};

class solid_color : public texture {
    public:
        solid_color();
        solid_color(color c);
        solid_color(float red, float green, float blue);
        virtual color value(float u, float v, const vec3& p)const;

    private:
        color color_value;
};

class checker_texture : public texture {
    //其实这是一个五维纹理，p的三个坐标决定了选哪张图片作为纹理
        //u和v又决定了在这张图片的什么位置取色，所以说是一个五维纹理
    public:
        checker_texture();
        checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd);
        checker_texture(color c1, color c2);
        //其实这是一个五维纹理，p的三个坐标决定了选哪张图片作为纹理
        //u和v又决定了在这张图片的什么位置取色，所以说是一个五维纹理
        virtual color value(float u, float v, const point3& p) const override;
    public:
        shared_ptr<texture> odd;
        shared_ptr<texture> even;
};

class noise_texture : public texture {
    public:
        noise_texture();
        noise_texture(float sc);
        virtual color value(float u, float v, const point3& p) const override;
    public:
        perlin noise;
        float scale;
};

class image_texture : public texture {
    public:
        image_texture();
        image_texture(const char* filename);
        ~image_texture();
        inline float clamp(float x, float min_val, float max_val)const;
        virtual color value(float u, float v, const vec3& p) const override;
    private:
        unsigned char *data;
        int width, height;
        int bytes_per_scanline;
        const static int bytes_per_pixel = 3;
};
#endif