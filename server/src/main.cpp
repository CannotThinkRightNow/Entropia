#include "server/main.hpp"
#include "core/utilities/io.hpp"
#include "core/utilities/logging.hpp"

#define SERVER_ID "Server"

boost::filesystem::path executable_path;

int main(const int argc, const char *argv[])
{
    io::init();
    executable_path = argv[0];
    logging::init();

    logging::printArgs(SERVER_ID, argc, argv);

    logging::terminate();
    return 0;
}

boost::filesystem::path getExecutablePath() { return executable_path; }
