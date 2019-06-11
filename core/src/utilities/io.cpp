#include "core/config.h"
#include "core/utilities/io.hpp"

#include "core/utilities/id.h"

#include <utility>

#include <iostream>
#include <sstream>
#include <fstream>

#ifdef CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

using namespace boost::filesystem;

namespace
{
    static io::files::details::executable_path_func_t executable_path_func;
}

namespace io
{
    void init()
    {
#ifdef CONFIG_PLATFORM_WINDOWS
        path::codecvt(); // Ensure VC++ does not race during initialization.
#elif defined(CONFIG_PLATFORM_UNIX) /* CONFIG_PLATFORM_WINDOWS */
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

        // i.close();
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

        // o.close();
        return true;
    }

    namespace files
    {
        path executable_path() noexcept { return (*executable_path_func)(); }

        path pointer_path()
        {
            static const path res = details::pointer_path();
            return res;
        }

        path data_path()
        {
            const path pp = files::pointer_path();
            if (!is_regular_file(pp)) remove_all(pp);

            std::string res;
            if (exists(pp) && !is_empty(pp)) read(pp, res);
            else res = default_data_path().string();

            boost::system::error_code errc;
            create_directories(path(res), errc);
            if (errc.failed()) res = default_data_path().string();

            write(pp, res);
            return path(res);
        }

        path default_data_path()
        {
            static const path res = details::default_data_path();
            return res;
        }

        namespace details
        {
            void set_executable_path_func(executable_path_func_t func) { std::swap(executable_path_func, func); }

            path pointer_path()
            {
                if (id::id_g() == id::CLIENT)
                {
#ifdef CONFIG_PLATFORM_WINDOWS
                    LPWSTR out;
                    if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &out)))
                    {
                        // No logging here.
                        throw std::runtime_error("Error while getting local app data directory path.");
                    }
                    const std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> ptr(out, &CoTaskMemFree);
                    return path(ptr.get()) / "pointer.txt";
#endif /* CONFIG_PLATFORM_WINDOWS */
                }
                else if (id::id_g() == id::SERVER)
                {
                    return files::default_data_path() / "pointer.txt";
                }
            }

            path default_data_path()
            {
                if (id::id_g() == id::CLIENT)
                {
#ifdef CONFIG_PLATFORM_WINDOWS
                    LPWSTR out;
                    if (FAILED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &out)))
                    {
                        // No logging here.
                        throw std::runtime_error("Error while getting roaming app data directory path.");
                    }
                    const std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> ptr(out, &CoTaskMemFree);
                    return path(ptr.get()) /= "data";
#endif /* CONFIG_PLATFORM_WINDOWS */
                }
                else if (id::id_g() == id::SERVER)
                {
                    return files::executable_path() /= "data";
                }
            }
        }
    }
}
