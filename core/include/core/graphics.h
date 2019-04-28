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

#include "core_export.h"

namespace graphics
{
    CORE_EXPORT extern bool glfwUnsupported;
    CORE_EXPORT extern GLFWmonitor* monitor;
    CORE_EXPORT extern GLFWwindow* window;
    CORE_EXPORT extern GLuint vertexBuffer;

    void createWindow();
    void glInit();

    void glfwErrorCallback(int error, const char* description);
}

#elif GLES_GRAPHICS /* GL_GRAPHICS */

#elif METAL_GRAPHICS /* GLES_GRAPHICS */

#endif /* METAL_GRAPHICS*/

#endif /* GRAPHICS_H_ */
