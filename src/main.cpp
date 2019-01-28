#include "Vec3.h"
#include "World.h"
#include "Tools.h"

#include <json.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

const std::string read_config_file(const std::string& config_file)
{
    std::ifstream file(config_file);

    if (file)
    {
        std::ostringstream buff;
        buff << file.rdbuf();

        std::string str_file = buff.str();

        file.close();
        return str_file;
    }
    else
    {
        Log::error("[CONFIGURATION] Error : you need to provide a valide JSON configuarion file");
        return "";
    }
}

int main(int argc, char const *argv[])
{
    std::string config_file;

    if (argc > 1)
    {
        config_file = read_config_file(argv[1]);
        if (config_file != "")
        {
            World world(config_file);
            world.build();
            world.render();
        }
    }
    else
        Log::error("[CONFIGURATION] Error : you need to provide a valide JSON configuarion file");

    return 0;
}