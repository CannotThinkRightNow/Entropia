#include "config.h"
#include "main.h"

#if PLATFORM_ANDROID
void glfwCreateWindow()
{
}
void glInit()
{
}
void loop()
{
}

#elif PLATFORM_IOS // PLATFORM_ANDROID
void glfwCreateWindow()
{
}
void glInit()
{
}
void loop()
{
}

#elif PLATFORM_MACOS // PLATFORM_IOS
void glfwCreateWindow()
{
}
void glInit()
{
}
void loop()
{
}

#elif PLATFORM_LINUX // PLATFORM_MACOS
void glfwCreateWindow()
{
}
void glInit()
{
}
void loop()
{
}

#elif PLATFORM_WINDOWS // PLATFORM_LINUX
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

    fprintf(stdout, "==========Monitors Information==========\n");
    fprintf(stdout, "All Monitors Combined Size: (%d, %d)\n", GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN));
    fprintf(stdout, "Primary Monitor Size: (%d, %d)\n", GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    fprintf(stdout, "Primary Monitor Work Area: %d\n", GetSystemMetrics(SPI_GETWORKAREA));
    
    window = glfwCreateWindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), NAME, glfwGetPrimaryMonitor(), nullptr);
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

#endif // PLATFORM_WINOWS

int main(int argc, char* argv[])
{
    fprintf(stdout, "==========Arguments==========\n");
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
