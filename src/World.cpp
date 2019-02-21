#include "World.h"
#include "Tools.h"
#include "Vec3.h"
#include "Sphere.h"

#include <json.hpp>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

World::World(const std::string& config_file) : m_config(config_file), m_height(0), m_width(0), m_background_color(Vec3(0))
{
}

void World::build()
{
    Log::basic("PBRRaytracer v0.1\n");
    Log::debug("Building...");
    
    auto config = nlohmann::json::parse(m_config);
    for (auto& item : config.items())
    {
        if (item.key() == "dimension")
        {
            for (auto& dimension : item.value().items())
            {
                if (dimension.key() == "width")
                    m_width = dimension.value();
                else if (dimension.key() == "height")
                    m_height = dimension.value();
            }
        }
        else if (item.key() == "background_color")
        {
            unsigned int r, g, b;
            for (auto& channel : item.value().items())
            {
                if (channel.key() == "r")
                    r = channel.value();
                else if (channel.key() == "g")
                    g = channel.value();
                else if (channel.key() == "b")
                    b = channel.value();
            }

            m_background_color = Vec3(r, g, b);
        }
        else if (item.key() == "entities")
        {
            for (auto& entity : item.value().items())
            {
                float x, y, z, radius;
                for (auto& setting : entity.value().items())
                {
                    if (setting.key() == "position")
                    {
                        for (auto& coordinate : setting.value().items())
                        {
                            if (coordinate.key() == "x")
                                x = coordinate.value();
                            else if (coordinate.key() == "y")
                                y = coordinate.value();
                            else if (coordinate.key() == "z")
                                z = coordinate.value();
                        }
                    }
                    else if (setting.key() == "radius")
                    {
                        radius = setting.value();
                    }
                }
                m_hitable_list.push_back(new Sphere(Vec3(x, y, z), radius));
            }
        }
    }

    Log::debug("Configuration : ");
    Log::basic(m_config.c_str());
    Log::basic("");
}

void World::render()
{
    Log::debug("Rendering...\n");
    std::string file_name = "../output/scene_" + Tools::current_data_time() + ".ppm";
    auto start = std::chrono::high_resolution_clock::now();

    fill_img(file_name);

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;

    std::string cmd = "../tools/imgcat ../output/" + file_name;
    std::system(cmd.c_str());

    std::ostringstream duration;
    duration << std::setprecision(2) << elapsed.count();
    Log::debug("\nRendering done in : " + duration.str() + "s");
}

void World::fill_img(const std::string& file_name)
{
    std::ofstream img(file_name);
    img << "P3" << std::endl;
    img << m_width << " " << m_height << std::endl;
    img << "255" << std::endl;

    Vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    Vec3 horizontal(4.0f, 0.0f, 0.0f);
    Vec3 vertical(0.0f, 2.0f, 0.0f);
    Vec3 origin(0.0f, 0.0f, 0.0f);

    for (int row = m_height - 1; row >= 0; row--)
    {
        for (int col = 0; col < m_width; col++)
        {
            float u = float(col) / float(m_width);
            float v = float(row) / float(m_height);

            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
            Vec3 color = compute_pixel(ray);

            int r = int(color.r() * 255.99);
            int g = int(color.g() * 255.99);
            int b = int(color.b() * 255.99);
            img << r << " " << g << " " << b << std::endl;
        }
    }

    img.close();
}

Vec3 World::compute_pixel(const Ray& ray)
{
    HitRecord hit_record;
    if (obj_is_hited(ray, 0.001f, MAXFLOAT, hit_record))
    {
        return 0.5f * Vec3(hit_record.normal.x() + 1, hit_record.normal.y() + 1, hit_record.normal.z() + 1);
    }
    return ranged_color(m_background_color);
}

bool World::obj_is_hited(const Ray& ray, float t_min, float t_max, HitRecord& hit_record)
{
    HitRecord tmp_record;
    bool hit_anything = false;
    double closest = t_max;

    for (auto const& hitable : m_hitable_list)
    {
        if (hitable->hit(ray, t_min, closest, tmp_record))
        {
            hit_anything = true;
            closest = tmp_record.t;
            hit_record = tmp_record;
        }
    }

    return hit_anything;
}