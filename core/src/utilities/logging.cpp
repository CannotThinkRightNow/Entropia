#include "logging.h"
#include "config.h"

#include <iostream>
#if WIDE_STRING
#include <sstream>
#endif /* WIDE_STRING */
#include <chrono>
#include <ctime>
#include <algorithm>

using system_clock = std::chrono::system_clock;

namespace logging
{
#if WIDE_STRING
    using char_t = wchar_t;
#else /* WIDE_STRING */
    using char_t = char;
#endif

    const string getNowTimeString()
    {
        std::time_t time = system_clock::to_time_t(system_clock::now());
#if SECURE_FUNCTIONS
        char time_c_str[26];
        ctime_s(time_c_str, sizeof time_c_str, &time);
#if WIDE_STRING
        std::wostringstream woss;
        woss << time_c_str;
        string time_str = woss.str();
#else /* WIDE_STRING */
        string time_str(time_c_str);
#endif
#else /* SECURE_FUNCTIONS */
        std::string time_str(ctime(&time));
#endif
        time_str.erase(std::remove_if(time_str.begin(), time_str.end(), [](const char_t c) { return c == string_('\n'); }), time_str.end());
        return time_str;
    }

    int println()
    {
#if WIDE_STRING
        return std::wprintf(L"\n");
#else /* WIDE_STRING */
        return std::printf("\n");
#endif
    }
    
    namespace utilities
    {
        void printArgs(string id, int argc, char** argv)
        {
            printlnf(Level::LEVEL_INFO, id, SECTION_HEADER_NAMED, string_("Arguments"));
            printlnf(Level::LEVEL_INFO, id, string_("Arguments Count: %d"), argc);
            printf(Level::LEVEL_INFO, id, string_("Arguments:"));
            for (int i = 0; i < argc; i++)
#if WIDE_STRING
            {
                std::wostringstream woss;
                woss << argv[i];
                std::wprintf(L" %s", woss.str().c_str());
            }
#else /* WIDE_STRING */
                std::printf(" %s", argv[i]);
#endif
            println();
            printlnf(Level::LEVEL_INFO, id, SECTION_FOOTER);
        }
    }
}
