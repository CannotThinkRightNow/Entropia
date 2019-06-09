#include "core/config.h"
#include "core/utilities/io.hpp"
#if CONFIG_PLATFORM_WINDOWS
#include <ShlObj.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

namespace io
{
    namespace files
    {
        namespace details
        {
            const path getDefaultDataPath()
            {
#if CONFIG_PLATFORM_WINDOWS
                LPWSTR o;
                if (FAILED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, KF_FLAG_DEFAULT, nullptr, &o)))
                {
                    // No logging here.
                    throw std::runtime_error("Error while getting roaming app data directory path.");
                }
                const std::unique_ptr<WCHAR, decltype(&CoTaskMemFree)> p(o, &CoTaskMemFree);
                return path(p.get());
#endif /* CONFIG_PLATFORM_WINDOWS */
            }
        }
    }
}
