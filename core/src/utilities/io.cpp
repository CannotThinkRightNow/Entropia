#include "core/utilities/io.hpp"

#include <string>
#if CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#include <boost/locale.hpp>
#endif /* CONFIG_PLATFORM_WINDOWS */
#include <boost/filesystem.hpp>

namespace io
{
    namespace files
    {
        const path getPointerPath()
        {
            static const path result = path(details::getPointerPath());
            return result;
        }

        namespace details
        {
            const std::string getPointerPath()
            {
#if CONFIG_PLATFORM_WINDOWS
                LPWSTR out;
                if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_DEFAULT, nullptr, &out)))
                {
                    // No logging here.
                    throw std::runtime_error("Error while getting local app data directory path.");
                }
                std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> p(out, &CoTaskMemFree);
                return boost::locale::conv::utf_to_utf<char>(p.get()) + "\\pointer.txt";
#endif /* CONFIG_PLATFORM_WINDOWS */
            }
        }
    }
}
