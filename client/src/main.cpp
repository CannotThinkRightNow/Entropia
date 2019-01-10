#include "utilities/logging.h"
#include "graphics.h"
#include "files.h"

#define CLIENT_ID "Client"

int main(int argc, char** argv)
{
    logging::init();
    logging::printArgs(CLIENT_ID, argc, argv);
    graphics::createWindow();
    graphics::glInit();
    
    while (!glfwWindowShouldClose(graphics::window))
    {
        glfwSwapBuffers(graphics::window);
        glfwPollEvents();
        if (glfwGetKey(graphics::window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(graphics::window, GL_TRUE);
    }
    
    glfwTerminate();
    logging::terminate();
    return 0;
}
