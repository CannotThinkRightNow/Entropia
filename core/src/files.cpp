#include "core/files.h"
#include "core/config.h"
#include "core/utilities/logging.h"

#define FILES_ID "Files"

#if CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#endif /* CONFIG_PLATFORM_WINDOWS */
#include <stdexcept>

namespace io
{
    File::File(std::string path) : path(path) {}
    const std::string File::getPath()
    {
        return path;
    }

    template<class T>
    SingletonFile<T>::SingletonFile(std::string path) : io::File(path){}

    namespace files
    {
        Pointer::Pointer() : SingletonFile<Pointer>(getPath()){}
        const std::string Pointer::getPath()
        {
            auto logger = logging::getLogger(FILES_ID);
#if CONFIG_PLATFORM_WINDOWS
            LPWSTR out;
            if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &out)))
            {
                std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> p(out, &CoTaskMemFree);
                return nullptr;
            }
            else
            {
                logger->info("Error while accessing local app data: %u", GetLastError());
                throw std::runtime_error("Error while accessing local app data.");
            }
#endif /* CONFIG_PLATFORM_WINDOWS */
        }
        const std::string Pointer::getDataPath()
        {
            return dataPath;
        }
    }
}
