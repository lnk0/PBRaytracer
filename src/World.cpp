#include "World.h"
#include "Tools.h"
#include "Vec3.h"

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
            Vec3 color = compute_color_of(ray);

            img << color.r() << " " << color.g() << " " << color.b() << std::endl;
        }
    }

    img.close();
}

Vec3 World::compute_color_of(const Ray& ray)
{
    return m_background_color;
}