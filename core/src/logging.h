#ifndef LOGGING_H
#define LOGGING_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <chrono>
#include <ctime>
#include <algorithm>

typedef const char* c_str;
using system_clock = std::chrono::system_clock;

#define SECTION_HEADER "=================================================="
#define SECTION_HEADER_NAMED "=========================%s========================="
#define SECTION_SPLITTER "--------------------------------------------------"
#define SECTION_FOOTER "=================================================="

namespace logging
{
    enum class Level : unsigned int
    {
        LEVEL_FATAL,
        LEVEL_ERROR,
        LEVEL_WARNING,
        LEVEL_INFO,
        LEVEL_DEBUG,
    };
    static const c_str levelNames[] = {"Fatal", "Error", "Warning", "Info", "Debug"};

    // Delete returned string after use.
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
        time_str.erase(std::remove_if(time_str.begin(), time_str.end(), [](const char& c){ return c == '\n'; }), time_str.end());
        char* ret = new char[time_str.length() + 1]();
#if SECURE_FUNCTIONS
        strcpy_s(ret, time_str.length() + 1, time_str.c_str());
#else
        strcpy(ret, time_str.c_str());
#endif
        return ret;
    }

    template<typename... Args>
    int printf(Level level, c_str id, c_str format, Args... args)
    {
        unsigned int levelValue = static_cast<unsigned int>(level);
        std::ostringstream oss;
        oss << "[%s] [%s] [%s] " << format;
        c_str time_str = getNowTimeString();
        int ret = std::printf(oss.str().c_str(), time_str, levelNames[levelValue], id, args...);
        delete time_str;
        return ret;
    }

    template<typename... Args>
    int printlnf(Level level, c_str id, c_str format, Args... args)
    {
        std::ostringstream oss;
        oss << format << "\n";
        return printf(level, id, oss.str().c_str(), args...);
    }

    int println()
    {
        return std::printf("\n");
    }

    namespace utility
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

#endif /* LOGGING_H */
