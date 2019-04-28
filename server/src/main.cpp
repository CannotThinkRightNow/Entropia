#include "core/utilities/logging.h"

#define SERVER_ID "Server"

int main(int argc, char** argv)
{
    logging::init();
    logging::printArgs(SERVER_ID, argc, argv);

    logging::terminate();
    return 0;
}
