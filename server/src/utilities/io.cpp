#include "core/config.h"
#include "core/utilities/io.hpp"
#include "server/main.hpp"

namespace io
{
    namespace files
    {
        namespace details
        {
            const path getDefaultDataPath() { return getExecutablePath(); }
        }
    }
}
