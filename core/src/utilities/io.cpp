#include "core/config.h"
#include "core/utilities/io.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

#if CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

using namespace boost::filesystem;

namespace io
{
    void init()
    {
#if CONFIG_PLATFORM_WINDOWS
        path::codecvt(); // Ensure VC++ does not race during initialization.
#elif CONFIG_PLATFORM_UNIX /* CONFIG_PLATFORM_WINDOWS */
        // std::locale(""); // Check whether environment variable for language is invalid.
#endif /* CONFIG_PLATFORM_UNIX */
    }


    bool read(const path file, std::string &out, const bool failfast = true, const std::iostream::openmode mode = std::iostream::in)
    {
        if (exists(file) && !is_regular_file(file)) return false;
        std::ifstream i;
        if (failfast) i.exceptions(std::ios::failbit);

        i.open(file.string(), mode);
        if (!i.good()) return false;

        i.seekg(0, std::ios::end);
        out.resize(i.tellg());
        i.seekg(0, std::ios::beg);
        i.read(&out[0], out.size());
        i.close();
        return true;
    }

    bool write(const path file, const std::string content, const bool failfast = true, const std::iostream::openmode mode = std::iostream::out)
    {
        if (exists(file) && !is_regular_file(file)) return false;
        std::ofstream o;
        if (failfast) o.exceptions(std::ios::failbit);

        o.open(file.string(), mode);
        if (!o.good()) return false;

        o << content;
        o.close();
        return true;
    }

    namespace files
    {
        const path getPointerPath()
        {
            static const path res = details::getPointerPath();
            return res;
        }

        const path getDataPath()
        {
            const path pp = files::getPointerPath();
            if (!is_regular_file(pp)) remove_all(pp);

            std::string res;
            if (exists(pp) && !is_empty(pp)) read(pp, res);
            else res = getDefaultDataPath().string();

            boost::system::error_code errc;
            create_directories(path(res), errc);
            if (errc.failed()) res = getDefaultDataPath().string();

            write(pp, res);
            return path(res);
        }

        const path getDefaultDataPath()
        {
            static const path res = details::getDefaultDataPath();
            return res;
        }

        namespace details
        {
            const path getPointerPath()
            {
#if CONFIG_PLATFORM_WINDOWS
                LPWSTR o;
                if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &o)))
                {
                    // No logging here.
                    throw std::runtime_error("Error while getting local app data directory path.");
                }
                const std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> p(o, &CoTaskMemFree);
                return path(p.get()) /= "pointer.txt";
#endif /* CONFIG_PLATFORM_WINDOWS */
            }
        }
    }
}
