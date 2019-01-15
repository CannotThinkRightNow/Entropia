##################################################
# Unnamed
##################################################

# Policies
cmake_minimum_required (VERSION 3.12)

# Project
project ("unnamed")
set (PROJECT_VERSION "0.0.1-v1-alpha")

include ("cmake/variables.cmake")
include (GNUInstallDirs)
include (FetchContent)
include ("cmake/GitModules.cmake")
include ("cmake/utilities.cmake")

GitModules_UpdateOrCheck ($ENV{CI})

# Dependencies
message (STATUS ${SECTION_HEADER})
message (STATUS "Dependencies")
message (STATUS ${SECTION_SPLITTER})
# Build
if (ANDROID) # OpenGL ES 2.0
  find_library (GLES2_LIB "libGLESv2.so" HINTS "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}")
  add_library (gles2 SHARED IMPORTED GLOBAL)
  set_target_properties (gles2 PROPERTIES IMPORTED_LOCATION ${GLES2_LIB})

  set (GRAPHICS_LIBRARY "GLES2")
elseif (IOS) # Metal
  # TODO: use Metal here...

  set (GRAPHICS_LIBRARY "METAL")
elseif (LINUX OR MACOS OR WINDOWS) # OpenGL
  # GLEW
  message (STATUS "Adding 'glew'...")
  include ("cmake/glew.cmake")
  message (STATUS "Successfully added 'glew'.")
  message (STATUS ${SECTION_SPLITTER})
  # GLFW
  message (STATUS "Adding 'glfw'...")
  FetchContent_Declare (glfw_project
                        SOURCE_DIR "${PROJECT_SOURCE_DIR}/glfw")
  message (STATUS "Successfully added 'glfw'.")
  message (STATUS ${SECTION_SPLITTER})

  set (GRAPHICS_LIBRARY "GL")
else () # Unknown
  message (FATAL_ERROR "Graphics library unknown.")
endif ()
# spdlog
message (STATUS "Adding 'spdlog'...")
FetchContent_Declare (spdlog_project
                      SOURCE_DIR "${PROJECT_SOURCE_DIR}/spdlog")
message (STATUS "Successfully added 'spdlog'.")
message (STATUS ${SECTION_FOOTER})

# Sub-projects
message (STATUS ${SECTION_HEADER})
message (STATUS "Building '${PROJECT_NAME}'...")
message (STATUS ${SECTION_SPLITTER})
# Core
message (STATUS "Building 'core'...")
add_subdirectory ("core")
message (STATUS "Successfully built 'core'.")
message (STATUS ${SECTION_SPLITTER})
# Server
message (STATUS "Building 'server'...")
add_subdirectory ("server")
message (STATUS "Successfully built 'server'.")
message (STATUS ${SECTION_SPLITTER})
# Client
message (STATUS "Building 'client'...")
add_subdirectory ("client")
message (STATUS "Successfully built 'client'.")
message (STATUS ${SECTION_SPLITTER})
message (STATUS "Successfully built '${PROJECT_NAME}'.")
message (STATUS ${SECTION_FOOTER})

# Packaging
install (FILES "COPYING.txt" "COPYING.md" "LICENSE-GPL-3.0.txt" "LICENSE-GPL-3.0.md" "LICENSE-CC-BY-4.0.txt" ${OUT_INCLUDE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include (CPack)
