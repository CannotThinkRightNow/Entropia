#include "utilities/logging.h"
#include "main.h"

namespace logUtilities = logging::utilities;

int main(int argc, char** argv)
{
    logUtilities::printArgs(SERVER_ID, argc, argv);
}
