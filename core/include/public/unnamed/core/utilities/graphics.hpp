#ifndef CORE_GRAPHICS_HPP_
#define CORE_GRAPHICS_HPP_

#pragma once

#include "config.h"

#ifdef CONFIG_PLATFORM_WINDOWS
#include <Windows.h> // Include before including <GLFW/glfw3.h>
#endif /* CONFIG_PLATFORM_WINDOWS */

#ifdef CONFIG_GL_GRAPHICS
#ifdef CONFIG_PLATFORM_MACOS
#include <OpenGL/glew.h>
#else /* CONFIG_PLATFORM_MACOS */
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include STR(CONFIG_NAMESPACE/core/export.h)

namespace CONFIG_NAMESPACE
{
    namespace graphics
    {
        CORE_EXPORT extern bool glfw_unsupported;
        CORE_EXPORT extern GLFWmonitor* monitor;
        CORE_EXPORT extern GLFWwindow* window;
        CORE_EXPORT extern GLuint vertex_buffer;

        void init();

        void create_window();

        void error_callback(const int error, const char* description);
    }
}

#elif defined(CONFIG_GLES_GRAPHICS) /* CONFIG_GL_GRAPHICS */

#elif defined(CONFIG_METAL_GRAPHICS) /* CONFIG_GLES_GRAPHICS */

#endif /* CONFIG_METAL_GRAPHICS */

#endif /* CORE_GRAPHICS_HPP_ */
