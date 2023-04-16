#include "texture.h"
#include "rtw_stb_image.h"
solid_color::solid_color() {}
solid_color::solid_color(color c) : color_value(c) {}
solid_color::solid_color(float red, float green, float blue):solid_color(color(red,green,blue)){}
color solid_color::value(float u, float v, const vec3& p) const {
    return color_value;
}

checker_texture::checker_texture() {}
checker_texture::checker_texture(shared_ptr<texture> _even, shared_ptr<texture> _odd): even(_even), odd(_odd) {}
checker_texture::checker_texture(color c1, color c2): even(make_shared<solid_color>(c1)) , odd(make_shared<solid_color>(c2)) {}
color checker_texture::value(float u, float v, const point3& p) const{
    auto sines = sin(10*p.x())*sin(10*p.y())*sin(10*p.z());
    if (sines < 0)
        return odd->value(u, v, p);
    else
        return even->value(u, v, p);
}

noise_texture::noise_texture():scale(1.0) {}
noise_texture::noise_texture(float sc) : scale(sc) {}
color noise_texture::value(float u, float v, const point3& p) const{
    return color(1,1,1) * 0.5 * (1 + sin(scale*p.z() + 10*noise.turb(p)));
}

image_texture::image_texture():data(nullptr), width(0), height(0), bytes_per_scanline(0){}
image_texture::image_texture(const char* filename) {
    auto components_per_pixel = bytes_per_pixel;

    data = stbi_load(
        filename, &width, &height, &components_per_pixel, components_per_pixel);

    if (!data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width = height = 0;
    }
    bytes_per_scanline = bytes_per_pixel * width;
}
image_texture::~image_texture() {
    delete data;
}
inline float image_texture::clamp(float x, float min_val, float max_val)const {
    if (x < min_val)
        return min_val;
    else if (x > max_val)
        return max_val;
    else
        return x;
}
color image_texture::value(float u, float v, const vec3& p) const{
    // If we have no texture data, then return solid cyan as a debugging aid.
    if (data == nullptr)
        return color(0,1,1);

    // Clamp input texture coordinates to [0,1] x [1,0]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);  // Flip V to image coordinates

    auto i = static_cast<int>(u * width);
    auto j = static_cast<int>(v * height);

    // Clamp integer mapping, since actual coordinates should be less than 1.0
    if (i >= width)  i = width-1;
    if (j >= height) j = height-1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = data + j*bytes_per_scanline + i*bytes_per_pixel;

    return color(color_scale*pixel[0], color_scale*pixel[1], color_scale*pixel[2]);
}