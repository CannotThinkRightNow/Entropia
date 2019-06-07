#include "core/graphics.h"
#include "core/utilities/logging.h"

#if CONFIG_PLATFORM_WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif /* CONFIG_PLATFORM_WINDOWS */
#include <stdexcept>

#define GRAPHICS_ID "Graphics"

#if CONFIG_PLATFORM_MACOS

#elif CONFIG_PLATFORM_LINUX /* CONFIG_PLATFORM_MACOS */

#elif CONFIG_PLATFORM_WINDOWS /* CONFIG_PLATFORM_LINUX */
#define VIRTUAL_X GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define VIRTUAL_Y GetSystemMetrics(SM_CYVIRTUALSCREEN)
#define PRIMARY_X GetSystemMetrics(SM_CXSCREEN)
#define PRIMARY_Y GetSystemMetrics(SM_CYSCREEN)
#endif /* CONFIG_PLATFORM_WINDOWS */

namespace graphics
{
#if CONFIG_GL_GRAPHICS
    bool glfwUnsupported = false;
    GLFWmonitor* monitor;
    GLFWwindow* window;
    GLuint vertexBuffer;
    
    void createWindow()
    {
        glfwSetErrorCallback(glfwErrorCallback);

        auto logger = logging::getLogger(GRAPHICS_ID);
        logger->info(SECTION_HEADER_NAMED, "GLFW");
        logger->info("Compiled-time version: %i.%i.%i", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
        int major, minor, revision;
        glfwGetVersion(&major, &minor, &revision);
        logger->info("Runtime version: %i.%i.%i", major, minor, revision);
        if (GLFW_VERSION_MAJOR != major || GLFW_VERSION_MINOR != minor || GLFW_VERSION_REVISION != revision)
        {
            glfwUnsupported = true;
            logger->warn("Compiled-time version and runtime version differs.");
            logger->warn("No support is provided by using a different version of GLFW!");
        }
        logger->info(SECTION_FOOTER);

        if (!glfwInit())
        {
            logger->critical("Failed to initialize glfw!");
            throw std::runtime_error("Failed to initialize glfw!");
        }

        // Require the OpenGL context to support OpenGL 3.2 at the least.
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        logger->info(SECTION_HEADER_NAMED, "Monitors");
#if CONFIG_PLATFORM_WINDOWS
        logger->info("Virtual Monitor Size: (%i, %i)", VIRTUAL_X, VIRTUAL_Y);
        logger->info("Primary Monitor Size: (%i, %i)", PRIMARY_X, PRIMARY_Y);
        logger->info("Primary Monitor Work Area : %i", GetSystemMetrics(SPI_GETWORKAREA));
#endif /* CONFIG_PLATFORM_WINDOWS */
        logger->info(SECTION_FOOTER);

        window = glfwCreateWindow(PRIMARY_X, PRIMARY_Y, CONFIG_NAME, glfwGetPrimaryMonitor(), nullptr);
        glfwMakeContextCurrent(window);
    }

    void glInit()
    {
        glewExperimental = GL_TRUE;
        glewInit();
        glGenBuffers(1, &vertexBuffer);
    }

    void glfwErrorCallback(int error, const char* description)
    {
        logging::getLogger("GLFW")->info("An error occured. Code: %i, Description: %s", error, description);
    }

#elif GLES_GRAPHICS /* CONFIG_GL_GRAPHICS */

#elif METAL_GRAPHICS /* CONFIG_GLES_GRAPHICS */

#endif /* CONFIG_METAL_GRAPHICS*/
}
