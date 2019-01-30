#pragma once

#include "Ray.h"

#include <string>

class World
{
private:
    std::string m_config;

    unsigned int m_width;
    unsigned int m_height;

    Vec3 m_background_color;

public:
    World(const std::string& config_file);

    void build();
    void render();

private:
    void fill_img(const std::string& file_name);
    Vec3 compute_color_of(const Ray& ray);
};