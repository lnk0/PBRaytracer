#include "World.h"
#include "Tools.h"

#include <json.hpp>
#include <fstream>
#include <sstream>
#include <chrono>
#include <iomanip>

World::World(const std::string& config_file) : m_config(config_file)
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

    for (int line = m_height - 1; line >= 0; line--)
    {
        for (int row = 0; row < m_width; row++)
        {
            img << "255" << " " << "255" << " " << "255" << std::endl;
        }
    }

    img.close();
}