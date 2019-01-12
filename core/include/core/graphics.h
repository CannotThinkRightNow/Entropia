#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#pragma once

#include "config.h"

#if GL_GRAPHICS
#if PLATFORM_MACOS
#include <OpenGL/glew.h>
#else /* PLATFORM_MACOS */
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

namespace graphics
{
    extern bool glfwUnsupported;
    extern GLFWmonitor* monitor;
    extern GLFWwindow* window;
    extern GLuint vertexBuffer;

    void createWindow();
    void glInit();

    void glfwErrorCallback(int error, const char* description);
}

#elif GLES_GRAPHICS /* GL_GRAPHICS */

#elif METAL_GRAPHICS /* GLES_GRAPHICS */

#endif /* METAL_GRAPHICS*/

#endif /* GRAPHICS_H_ */
