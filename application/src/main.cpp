#include "config.h"
#include "vars.h"

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

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#if GL_GRAPHICS
GLFWmonitor* monitor;
GLFWwindow* window;
GLuint vertexBuffer;

void glCreateWindow()
{
    glfwInit();

    // Require the OpenGL context to support OpenGL 3.2 at the least.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    fprintf(stdout, SECTION_HEADER_NAMED, "Monitors Information");
#if PLATFORM_WINDOWS
    fprintf(stdout, "Virtual Monitor Size: (%d, %d)\n", VIRTUAL_X, VIRTUAL_Y);
    fprintf(stdout, "Primary Monitor Size: (%d, %d)\n", PRIMARY_X, PRIMARY_Y);
    fprintf(stdout, "Primary Monitor Work Area: %d\n", GetSystemMetrics(SPI_GETWORKAREA));
#endif /* PLATFORM_WINDOWS */
    fprintf(stdout, SECTION_FOOTER);
    
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
    fprintf(stdout, SECTION_HEADER_NAMED, "Arguments");
    fprintf(stdout, "Arguments Count: %d\n", argc);
    fprintf(stdout, "Arguments:");
    for (int i = 0; i < argc; i++)
        fprintf(stdout, " %s", argv[i]);
    fprintf(stdout, "\n");

    glCreateWindow();
    glInit();
    loop();
    glfwTerminate();
    return 0;
}
