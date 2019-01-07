#ifndef LOGGING_H
#define LOGGING_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>

typedef const char* String;
typedef String Level;

#define LEVEL_DEBUG "Debug"
#define LEVEL_INFO "Info"
#define LEVEL_WARNING "Warning"
#define LEVEL_ERROR "Error"

template<typename... Args>
int printf(Level level, String id, String format, Args... args)
{
    std::ostringstream oss;
    oss << "\[%s\] \[%s\] " << format;
    return std::printf(oss.str().c_str(), level, id, args...);
}

template<typename... Args>
int printlnf(Level level, String id, String format, Args... args)
{
    std::ostringstream oss;
    oss << "\[%s\] \[%s\] " << format << "\n";
    return std::printf(oss.str().c_str(), level, id, args...);
}
int println()
{
    return std::printf("\n");
}

#define SECTION_HEADER "=================================================="
#define SECTION_HEADER_NAMED "=========================%s========================="
#define SECTION_SPLITTER "--------------------------------------------------"
#define SECTION_FOOTER "=================================================="

#endif /* LOGGING_H */
