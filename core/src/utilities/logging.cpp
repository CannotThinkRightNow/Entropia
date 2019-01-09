#include "logging.h"
#include "config.h"

#include <iostream>
#include <chrono>
#include <ctime>
#include <algorithm>

using system_clock = std::chrono::system_clock;

namespace logging
{
    c_str getNowTimeString()
    {
        std::time_t time = system_clock::to_time_t(system_clock::now());
#if SECURE_FUNCTIONS
        char time_c_str[26];
        ctime_s(time_c_str, sizeof time_c_str, &time);
        std::string time_str(time_c_str);
#else
        std::string time_str(ctime(&time));
#endif
        time_str.erase(std::remove_if(time_str.begin(), time_str.end(), [](const char& c) { return c == '\n'; }), time_str.end());
        char* ret = new char[time_str.length() + 1]();
#if SECURE_FUNCTIONS
        strcpy_s(ret, time_str.length() + 1, time_str.c_str());
#else
        strcpy(ret, time_str.c_str());
#endif
        return ret;
    }

    // template<typename... Args>
    // int printf(Level level, c_str id, c_str format, Args... args);

    // template<typename... Args>
    // int printlnf(Level level, c_str id, c_str format, Args... args);

    int println()
    {
        return std::printf("\n");
    }
    
    namespace utilities
    {
        void printArgs(c_str id, int argc, char** argv)
        {
            printlnf(Level::LEVEL_INFO, id, SECTION_HEADER_NAMED, "Arguments");
            printlnf(Level::LEVEL_INFO, id, "Arguments Count: %d", argc);
            printf(Level::LEVEL_INFO, id, "Arguments:");
            for (int i = 0; i < argc; i++)
                std::printf(" %s", argv[i]);
            println();
            printlnf(Level::LEVEL_INFO, id, SECTION_FOOTER);
        }
    }
}
