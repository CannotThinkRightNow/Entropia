#ifndef MAIN_H
#define MAIN_H
#pragma once

#include "config.h"

#if PLATFORM_ANDROID
#elif PLATFORM_IOS // PLATFORM_ANDROID
#elif PLATFORM_MACOS // PLATFORM_IOS
#elif PLATFORM_LINUX // PLATFORM_MACOS
#elif PLATFORM_WINDOWS // PLATFORM_LINUX
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <WinUser.h>

using namespace std;

#endif // PLATFORM_WINDOWS

#endif // MAIN_H
