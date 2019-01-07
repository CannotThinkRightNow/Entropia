#include "config.h"
#include "logging.h"

#define ID "Main"

#include <stdexcept>
#if GL_GRAPHICS
#if PLATFORM_MACOS
#include <OpenGL/glew.h>
#else /* PLATFORM_MACOS */
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#if PLATFORM_MACOS

#elif PLATFORM_LINUX /* PLATFORM_MACOS */

#elif PLATFORM_WINDOWS /* PLATFORM_LINUX */
#define VIRTUAL_X GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define VIRTUAL_Y GetSystemMetrics(SM_CYVIRTUALSCREEN)
#define PRIMARY_X GetSystemMetrics(SM_CXSCREEN)
#define PRIMARY_Y GetSystemMetrics(SM_CYSCREEN)
#endif /* PLATFORM_WINDOWS */
#elif GLES_GRAPHICS /* GL_GRAPHICS */

#elif METAL_GRAPHICS /* GLES_GRAPHICS */

#endif /* METAL_GRAPHICS */

#if PLATFORM_WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif /* PLATFORM_WINDOWS */

#if GL_GRAPHICS
GLFWmonitor* monitor;
GLFWwindow* window;
GLuint vertexBuffer;

void glCreateWindow()
{
    if (!glfwInit())
    {
        printlnf(LEVEL_ERROR, ID, "Failed to initialize glfw!");
        throw std::runtime_error("Failed to initialize glfw!");
    }

    // Require the OpenGL context to support OpenGL 3.2 at the least.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    printlnf(LEVEL_INFO, ID, SECTION_HEADER_NAMED, "Monitors Information");
#if PLATFORM_WINDOWS
    printlnf(LEVEL_INFO, ID, "Virtual Monitor Size: (%d, %d)", VIRTUAL_X, VIRTUAL_Y);
    printlnf(LEVEL_INFO, ID, "Primary Monitor Size: (%d, %d)", PRIMARY_X, PRIMARY_Y);
    printlnf(LEVEL_INFO, ID, "Primary Monitor Work Area: %d", GetSystemMetrics(SPI_GETWORKAREA));
#endif /* PLATFORM_WINDOWS */
    printlnf(LEVEL_INFO, ID, SECTION_FOOTER);
    
    window = glfwCreateWindow(PRIMARY_X, PRIMARY_Y, NAME, glfwGetPrimaryMonitor(), nullptr);
    glfwMakeContextCurrent(window);
}
void glInit()
{
    glewExperimental = GL_TRUE;
    glewInit();
    glGenBuffers(1, &vertexBuffer);
}
void loop()
{
    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
#elif GLES_GRAPHICS /* GL_GRAPHICS */

#elif METAL_GRAPHICS /* GLES_GRAPHICS */

#endif /* METAL_GRAPHICS */

int main(int argc, char* argv[])
{
    printlnf(LEVEL_INFO, ID, SECTION_HEADER_NAMED, "Arguments");
    printlnf(LEVEL_INFO, ID, "Arguments Count: %d", argc);
    printf(LEVEL_INFO, ID, "Arguments:");
    for (int i = 0; i < argc; i++)
        printf(" %s", argv[i]);
    println();
    printlnf(LEVEL_INFO, ID, SECTION_FOOTER);

    glCreateWindow();
    glInit();
    loop();
    glfwTerminate();
    return 0;
}
