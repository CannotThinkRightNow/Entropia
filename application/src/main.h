#ifndef MAIN_H
#define MAIN_H
#pragma once

#include "config.h"

#if GL_GRAPHICS
#if PLATFORM_MACOS
#include <OpenGL/glew.h>
#else // PLATFORM_MACOS
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>

#if PLATFORM_MACOS

#elif PLATFORM_LINUX // PLATFORM_MACOS

#elif PLATFORM_WINDOWS // PLATFORM_LINUX
#define VIRTUAL_X GetSystemMetrics(SM_CXVIRTUALSCREEN)
#define VIRTUAL_Y GetSystemMetrics(SM_CYVIRTUALSCREEN)
#define PRIMARY_X GetSystemMetrics(SM_CXSCREEN)
#define PRIMARY_Y GetSystemMetrics(SM_CYSCREEN)
#endif // PLATFORM_WINDOWS
#elif GLES_GRAPHICS // GL_GRAPHICS

#elif METAL_GRAPHICS // GLES_GRAPHICS

#endif // METAL_GRAPHICS

#if PLATFORM_WINDOWS
#include <Windows.h>
#include <WinUser.h>
#endif // PLATFORM_WINDOWS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#endif // MAIN_H
