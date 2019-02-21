#pragma once

#include "Ray.h"
#include "GeometricObj.h"

#include <string>
#include <vector>

class World
{
private:
    std::string m_config;

    unsigned int m_width;
    unsigned int m_height;

    Vec3 m_background_color;

    std::vector<GeometricObj *> m_hitable_list;

public:
    World(const std::string& config_file);

    void build();
    void render();

private:
    void fill_img(const std::string& file_name);
    Vec3 compute_pixel(const Ray& ray);
    bool obj_is_hited(const Ray& ray, float t_min, float t_max, HitRecord& hit_record);
};