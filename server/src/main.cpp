#include "logging.h"
#include "main.h"

namespace logUtility = logging::utility;

int main(int argc, char** argv)
{
    logUtility::printArgs(SERVER_ID, argc, argv);
}
