#include "config.h"
#include STR(CONFIG_NAMESPACE/core/utilities/graphics.hpp)
#include STR(CONFIG_NAMESPACE/core/logging.hpp)

#ifdef CONFIG_PLATFORM_WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

#include <stdexcept>

#define GRAPHICS_ID "Graphics"

#ifdef CONFIG_PLATFORM_MACOS

#elif defined(CONFIG_PLATFORM_UNIX) /* CONFIG_PLATFORM_MACOS */

#elif defined(CONFIG_PLATFORM_WINDOWS) /* CONFIG_PLATFORM_UNIX */
#define VIRTUAL_X GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define VIRTUAL_Y GetSystemMetrics(SM_CYVIRTUALSCREEN)
#define PRIMARY_X GetSystemMetrics(SM_CXSCREEN)
#define PRIMARY_Y GetSystemMetrics(SM_CYSCREEN)
#endif /* CONFIG_PLATFORM_WINDOWS */

using namespace std;
using namespace CONFIG_NAMESPACE;

namespace CONFIG_NAMESPACE
{
    namespace graphics
    {
#ifdef CONFIG_GL_GRAPHICS
        bool glfw_unsupported = false;
        GLFWmonitor* monitor;
        GLFWwindow* window;
        GLuint vertex_buffer;

        void init()
        {
            glewExperimental = GL_TRUE;
            glewInit();
            glGenBuffers(1, &vertex_buffer);
        }

        void create_window()
        {
            glfwSetErrorCallback(error_callback);

            const auto logger = logging::logger(GRAPHICS_ID);
            logger->info(SECTION_HEADER_NAMED, "GLFW");
            logger->info("Compile-time version: {:d}.{:d}.{:d}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
            int major, minor, revision;
            glfwGetVersion(&major, &minor, &revision);
            logger->info("Runtime version: {:d}.{:d}.{:d}", major, minor, revision);
            logger->info("Runtime version string: {:s}", glfwGetVersionString());
            if (GLFW_VERSION_MAJOR != major || GLFW_VERSION_MINOR != minor || GLFW_VERSION_REVISION != revision)
            {
                glfw_unsupported = true;
                logger->warn("Compile-time version and runtime version differs.");
                logger->warn("No support is provided by using a different version of GLFW.");
            }
            logger->info(SECTION_FOOTER);

            if (!glfwInit())
            {
                logger->critical("Failed to initialize glfw.");
                throw runtime_error("Failed to initialize glfw.");
            }

            // Require the OpenGL context to support OpenGL 3.2 at the least.
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

            logger->info(SECTION_HEADER_NAMED, "Monitors");
#ifdef CONFIG_PLATFORM_WINDOWS
            logger->info("Virtual Monitor Size: ({:d}, {:d})", VIRTUAL_X, VIRTUAL_Y);
            logger->info("Primary Monitor Size: ({:d}, {:d})", PRIMARY_X, PRIMARY_Y);
            logger->info("Primary Monitor Work Area : {:d}", GetSystemMetrics(SPI_GETWORKAREA));
#endif /* CONFIG_PLATFORM_WINDOWS */
            logger->info(SECTION_FOOTER);

            window = glfwCreateWindow(PRIMARY_X, PRIMARY_Y, CONFIG_NAME, glfwGetPrimaryMonitor(), nullptr);
            if (!window)
            {
                logger->critical("Failed to create window.");
                throw runtime_error("Failed to create window.");
            }
            glfwMakeContextCurrent(window);

            glfwSwapInterval(1);
        }

        void error_callback(const int error, const char* description)
        {
            logging::logger("GLFW")->info("An error occured. Code: {:d}, Description: {:s}", error, description);
        }

#elif defined(GLES_GRAPHICS) /* CONFIG_GL_GRAPHICS */

#elif defined(METAL_GRAPHICS) /* CONFIG_GLES_GRAPHICS */

#endif /* CONFIG_METAL_GRAPHICS*/
    }
}
