#pragma once
#ifndef MAIN_H
#define MAIN_H

#include "config.h"

#if PLATFORM_ANDROID
#elif PLATFORM_IOS
#elif PLATFORM_MACOS
#else
#include <GL/glew.h>
#endif

#endif // MAIN_H
