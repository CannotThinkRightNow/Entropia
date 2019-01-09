#include "files.h"
#include "utilities/logging.h"

#define FILES_ID string_("Files")

#if PLATFORM_WINDOWS
#include <ShlObj.h>
#endif
#include <stdexcept>

using logLevel = logging::Level;

namespace io
{
    File::File(string path) : path(path) {}
    const string File::getPath()
    {
        return path;
    }

    template<class T>
    SingletonFile<T>::SingletonFile(string path) : io::File(path){}

    namespace files
    {
        Pointer::Pointer() : SingletonFile<Pointer>(getPath()){}
        const string Pointer::getPath()
        {
#if PLATFORM_WINDOWS
            LPWSTR out;
            if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &out)))
            {
                std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> p(out, &CoTaskMemFree);
                string ret(out);
                return ret;
            }
            else
            {
                logging::printlnf(logLevel::LEVEL_FATAL, FILES_ID, string_("Error while accessing local app data: %u"), GetLastError());
                throw std::runtime_error("Error while accessing local app data.");
            }
#endif
        }
        const string Pointer::getDataPath()
        {
            return dataPath;
        }
    }
}
