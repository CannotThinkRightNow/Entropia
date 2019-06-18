##################################################
# Locate OpenGL ES 2.0
#
# This module defines:
#
# GLES2_FOUND - True if OpenGL ES 2.0 was found
# GLES2_LIBRARY - OpenGL ES 2.0 library path
# GLES2_INCLUDE - OpenGL ES 2.0 include headers
# GLES2_INCLUDE_DIR - OpenGL ES 2.0 include directory
#
# gles2 - Target for OpenGL ES 2.0
##################################################

include(FindPackageHandleStandardArgs)

message(STATUS "Finding GLES2...")

set(GLES2_LIBRARY)
find_library(GLES2_LIBRARY "libGLESv2" "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}/usr/lib")
set(GLES2_INCLUDE_DIR "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}/usr/include")
file(GLOB_RECURSE GLES2_INCLUDE "${GLES2_INCLUDE_DIR}/GLES2/*")

find_package_handle_standard_args(GLES2 DEFAULT_MSG
                                  GLES2_LIBRARY GLES2_INCLUDE_DIR GLES2_INCLUDE)

if (GLES2_FOUND)
  add_library(gles2 SHARED IMPORTED GLOBAL)
  set_target_properties(gles2 PROPERTIES IMPORTED_LOCATION ${GLES2_LIBRARY}
                                         PUBLIC_HEADER "${GLES2_INCLUDE}")
  target_include_directories(gles2 SYSTEM INTERFACE ${GLES2_INCLUDE_DIR})
endif ()
