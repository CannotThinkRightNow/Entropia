#include "logging.h"

#ifndef SERVER_ID
#define SERVER_ID "Server"
#endif

namespace logUtility = logging::utility;

int main(int argc, char** argv)
{
    logUtility::printArgs(SERVER_ID, argc, argv);
}
