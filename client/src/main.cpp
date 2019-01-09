#include "utilities/logging.h"
#include "main.h"
#include "graphics.h"
#include "files.h"

namespace logUtilities = logging::utilities;

int main(int argc, char** argv)
{
    logUtilities::printArgs(CLIENT_ID, argc, argv);
    graphics::createWindow();
    graphics::glInit();
    
    while (!glfwWindowShouldClose(graphics::window))
    {
        glfwSwapBuffers(graphics::window);
        glfwPollEvents();
        if (glfwGetKey(graphics::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(graphics::window, GL_TRUE);
    }
    
    return 0;
}
