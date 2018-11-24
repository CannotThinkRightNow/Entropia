#include "config.h"
#include "main.h"

int main(int argc, char* argv[])
{
    glewExperimental = GL_TRUE;
    glewInit();
    return 0;
}
