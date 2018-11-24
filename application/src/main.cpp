#include "main.h"

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

    fprintf(stdout, "==========Monitors Information==========\n");
#if PLATFORM_WINDOWS
    fprintf(stdout, "Virtual Monitor Size: (%d, %d)\n", VIRTUAL_X, VIRTUAL_Y);
    fprintf(stdout, "Primary Monitor Size: (%d, %d)\n", PRIMARY_X, PRIMARY_Y);
    fprintf(stdout, "Primary Monitor Work Area: %d\n", GetSystemMetrics(SPI_GETWORKAREA));
#endif // PLATFORM_WINDOWS
    
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
#elif GLES_GRAPHICS // GL_GRAPHICS

#elif METAL_GRAPHICS // GLES_GRAPHICS

#endif // METAL_GRAPHICS

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
