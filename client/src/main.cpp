#include "client/main.hpp"

#include "core/utilities/id.h"

#include "core/utilities/io.hpp"
#include "core/utilities/logging.hpp"
#include "core/graphics.hpp"

#define CLIENT_ID "Client"

namespace
{
    static boost::filesystem::path executable_path_;
}

int main(const int argc, const char *argv[])
{
    id::set_id(id::CLIENT);
    io::init();
    executable_path_ = argv[0];
    io::files::details::set_executable_path_func(&executable_path);
    logging::init();

    logging::print_args(CLIENT_ID, argc, argv);

    graphics::create_window();
    graphics::init();
    
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

boost::filesystem::path executable_path() noexcept { return executable_path_; }
