#include "server/main.hpp"

#include "core/utilities/id.h"

#include "core/utilities/io.hpp"
#include "core/utilities/logging.hpp"

#define SERVER_ID "Server"

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

boost::filesystem::path executable_path() noexcept { return executable_path_; }
