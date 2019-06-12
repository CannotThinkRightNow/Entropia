#include "config.h"
#include STR(CONFIG_NAMESPACE/server/main.hpp)

#include STR(CONFIG_NAMESPACE/core/utilities/id.h)

#include STR(CONFIG_NAMESPACE/core/utilities/io.hpp)
#include STR(CONFIG_NAMESPACE/core/utilities/logging.hpp)

#define SERVER_ID "Server"

using namespace CONFIG_NAMESPACE;

namespace
{
    static boost::filesystem::path executable_path_;
}

int main(const int argc, const char *argv[])
{
    id::set_id(id::SERVER);
    io::init();
    executable_path_ = argv[0];
    io::files::details::set_executable_path_func(&executable_path);
    logging::init();

    logging::print_args(SERVER_ID, argc, argv);

    logging::terminate();
    return 0;
}

namespace CONFIG_NAMESPACE
{
    boost::filesystem::path executable_path() noexcept { return executable_path_; }
}
