#ifndef LOGGING_H_
#define LOGGING_H_

#pragma once

#include "config.h"

#include <iostream>
#include <sstream>

#define SECTION_HEADER string_("==================================================")
#define SECTION_HEADER_NAMED string_("=========================%s=========================")
#define SECTION_SPLITTER string_("--------------------------------------------------")
#define SECTION_FOOTER string_("==================================================")

namespace logging
{
#if WIDE_STRING
    using string = std::wstring;
#else /* WIDE_STRING */
    using string = std::string;
#endif

    enum class Level : unsigned int
    {
        LEVEL_FATAL,
        LEVEL_ERROR,
        LEVEL_WARNING,
        LEVEL_INFO,
        LEVEL_DEBUG,
    };

    static const string levelNames[] = { string_("Fatal"), string_("Error"), string_("Warning"), string_("Info"), string_("Debug") };

    const string getNowTimeString();

#if WIDE_STRING
    // Do not include std::wstring in args.
    template<typename... Args>
    int printf(Level level, string id, string format, Args... args)
    {
        unsigned int levelValue = static_cast<unsigned int>(level);
        std::wostringstream woss;
        woss << L"[%s] [%s] [%s] " << format;
        return std::wprintf(woss.str().c_str(), getNowTimeString().c_str(), levelNames[levelValue].c_str(), id.c_str(), args...);
    }

    // Do not include std::wstring in args.
    template<typename... Args>
    int printlnf(Level level, string id, string format, Args... args)
    {
        std::wostringstream woss;
        woss << format << L"\n";
        return printf(level, id, woss.str(), args...);
    }

#else /* WIDE_STRING */
    // Do not include std::string in args.
    template<typename... Args>
    int printf(Level level, string id, string format, Args... args)
    {
        unsigned int levelValue = static_cast<unsigned int>(level);
        std::ostringstream oss;
        oss << "[%s] [%s] [%s] " << format;
        return std::printf(oss.str().c_str(), getNowTimeString().c_str(), levelNames[levelValue].c_str(), id.c_str(), args...);
    }

    // Do not include std::string in args.
    template<typename... Args>
    int printlnf(Level level, string id, string format, Args... args)
    {
        std::ostringstream oss;
        oss << format << "\n";
        return printf(level, id, oss.str(), args...);
    }

#endif

    int println();

    namespace utilities
    {
        void printArgs(string id, int argc, char** argv);
    }
}

#endif /* LOGGING_H_ */
