#pragma once

#include <iostream>

class Tools
{
public:
    static inline const std::string current_data_time()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];

        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }
    
};

class Log
{
public:
    static inline void error(const std::string& str)
    {
        std::cout << "\e[31m" << str.c_str() << "\e[0m" << std::endl;
    }

    static inline void debug(const std::string& str)
    {
        std::cout << "\e[34m" << str.c_str() << "\e[0m" << std::endl;
    }

    static inline void info(const std::string& str)
    {
        std::cout << "\e[32m" << str.c_str() << "\e[0m" << std::endl;
    }

    static inline void basic(const std::string& str)
    {
        std::cout << str.c_str() << std::endl;   
    }
};