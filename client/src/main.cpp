#include "core/utilities/io.hpp"
#include "core/utilities/logging.hpp"
#include "core/graphics.hpp"

#define CLIENT_ID "Client"

int main(const int argc, const char *argv[])
{
    io::init();
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
