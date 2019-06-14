#include "config.h"
#include STR(CONFIG_NAMESPACE/core/utilities/io.hpp)

#include STR(CONFIG_NAMESPACE/core/utilities/id.h)

#include <utility>

#include <iostream>
#include <sstream>
#include <fstream>

#ifdef CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

#include <boost/thread/thread.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

using namespace std;
using namespace CONFIG_NAMESPACE;
using namespace boost::filesystem;

namespace
{
    static io::files::details::executable_path_func_t executable_path_func;
    static boost::shared_mutex file_mutex;
}

namespace CONFIG_NAMESPACE
{
    namespace io
    {
        void init()
        {
#ifdef CONFIG_PLATFORM_WINDOWS
            path::codecvt(); // Ensure VC++ does not race during initialization.
#elif defined(CONFIG_PLATFORM_UNIX) /* CONFIG_PLATFORM_WINDOWS */
            // locale(""); // Check whether environment variable for language is invalid.
#endif /* CONFIG_PLATFORM_UNIX */
        }

        bool read(const path file, string &out, const bool failfast = true, const iostream::openmode mode = iostream::in, const bool blocking = true)
        {
            if (exists(file) && !is_regular_file(file)) return false;
            {
                boost::interprocess::scoped_lock<boost::shared_mutex> l(file_mutex, boost::interprocess::defer_lock);
                if (blocking) l.lock();
                else if (!l.try_lock()) return false;

                std::ifstream i;
                if (failfast) i.exceptions(ios::failbit);

                i.open(file.string(), mode);
                if (!i.good()) return false;

                i.seekg(0, ios::end);
#pragma warning(suppress: 4244)
                out.resize(i.tellg());
                i.seekg(0, ios::beg);
                i.read(&out[0], out.size());

                // i.close();
                // l.unlock();
            }
            return true;
        }

        bool write(const path file, const string content, const bool failfast = true, const iostream::openmode mode = iostream::out, const bool blocking = true)
        {
            if (exists(file) && !is_regular_file(file)) return false;
            {
                boost::interprocess::scoped_lock<boost::shared_mutex> l(file_mutex, boost::interprocess::defer_lock);
                if (blocking) l.lock();
                else if (!l.try_lock()) return false;

                std::ofstream o;
                if (failfast) o.exceptions(ios::failbit);

                o.open(file.string(), mode);
                if (!o.good()) return false;

                o << content;

                // o.close();
                // l.unlock();
            }
            return true;
        }

        namespace files
        {
            path executable_path() noexcept
            {
                static const path res = (*executable_path_func)();
                return res;
            }

            path executable_dir() noexcept
            {
                static const path res = executable_path().parent_path();
                return res;
            }

            path pointer_path()
            {
                static const path res = details::pointer_path();
                return res;
            }

            path data_path()
            {
                const path pptr = files::pointer_path();
                if (!is_regular_file(pptr)) remove_all(pptr);

                string res;
                if (exists(pptr) && !boost::filesystem::is_empty(pptr)) read(pptr, res);
                else res = default_data_path().string();

                boost::system::error_code errc;
                create_directories(path(res), errc);
                if (errc.failed()) res = default_data_path().string();

                write(pptr, res);
                return path(res);
            }

            path default_data_path()
            {
                static const path res = details::default_data_path();
                return res;
            }

            namespace details
            {
                void set_executable_path_func(executable_path_func_t func) { swap(executable_path_func, func); }

                path pointer_path()
                {
                    if (id::id_g() == id::CLIENT)
                    {
#ifdef CONFIG_PLATFORM_WINDOWS
                        LPWSTR out;
                        if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &out)))
                        {
                            // No logging here.
                            throw runtime_error("Error while getting local app data directory path.");
                        }
                        const unique_ptr<WCHAR, decltype(&CoTaskMemFree)> ptr(out, &CoTaskMemFree);
                        return path(ptr.get()) / CONFIG_NAME / "pointer.txt";
#endif /* CONFIG_PLATFORM_WINDOWS */
                    }
                    else if (id::id_g() == id::SERVER)
                    {
                        return files::executable_dir() / "pointer.txt";
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
                            throw runtime_error("Error while getting roaming app data directory path.");
                        }
                        const unique_ptr<WCHAR, decltype(&CoTaskMemFree)> ptr(out, &CoTaskMemFree);
                        return path(ptr.get()) / CONFIG_NAME;
#endif /* CONFIG_PLATFORM_WINDOWS */
                    }
                    else if (id::id_g() == id::SERVER)
                    {
                        return files::executable_dir() / "data";
                    }
                }
            }
        }
    }
}
