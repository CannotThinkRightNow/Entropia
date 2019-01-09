#ifndef LOGGING_H_
#define LOGGING_H_

#pragma once

#include "typedefs.h"

#include <iostream>
#include <sstream>

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
    static const c_str levelNames[] = { "Fatal", "Error", "Warning", "Info", "Debug" };

    // Returned string should be 'delete[]'ed.
    c_str getNowTimeString();

    template<typename... Args>
    int printf(Level level, c_str id, c_str format, Args... args)
    {
        unsigned int levelValue = static_cast<unsigned int>(level);
        std::ostringstream oss;
        oss << "[%s] [%s] [%s] " << format;
        c_str time_str = getNowTimeString();
        int ret = std::printf(oss.str().c_str(), time_str, levelNames[levelValue], id, args...);
        delete[] time_str;
        return ret;
    }

    template<typename... Args>
    int printlnf(Level level, c_str id, c_str format, Args... args)
    {
        std::ostringstream oss;
        oss << format << "\n";
        return printf(level, id, oss.str().c_str(), args...);
    }

    int println();

    namespace utilities
    {
        void printArgs(c_str id, int argc, char** argv);
    }
}

#endif /* LOGGING_H_ */
