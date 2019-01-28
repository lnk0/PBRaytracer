#pragma once

#include <string>

class World
{
private:
    std::string m_config;

    unsigned int m_width;
    unsigned int m_height;

public:
    World(const std::string& config_file);

    void build();
    void render();

private:
    void fill_img(const std::string& file_name);
};