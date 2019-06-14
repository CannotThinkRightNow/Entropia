##################################################
# Dependencies
##################################################

GitModules_UpdateOrCheck($ENV{CI})
message(STATUS ${SECTION_HEADER})
message(STATUS "Dependencies")
message(STATUS ${SECTION_SPLITTER})
# Boost
message(STATUS "Adding 'boost'...")
find_package(Boost ${Boost_MINIMUM_VERSION} REQUIRED COMPONENTS ${Boost_COMPONENTS})
message(STATUS "Successfully added 'boost'.")
message(STATUS ${SECTION_SPLITTER})
# Graphics
if (ANDROID) # OpenGL ES 2.0
  message(STATUS "Adding 'gles2'...")
  find_library(GLES2_LIB "libGLESv2.so" HINTS "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}")
  add_library(gles2 SHARED IMPORTED GLOBAL)
  set_target_properties(gles2 PROPERTIES IMPORTED_LOCATION ${GLES2_LIB})
  message(STATUS "Successfully added 'gles2'.")
  message(STATUS ${SECTION_SPLITTER})

  set(GRAPHICS_LIBRARY "GLES2")
elseif (IOS) # Metal
  # TODO: use Metal here...

  set(GRAPHICS_LIBRARY "METAL")
elseif (UNIX OR MACOS OR WINDOWS) # OpenGL
  # GLEW
  message(STATUS "Adding 'glew'...")
  include("cmake/glew.cmake")
  glew_project_Declare()
  message(STATUS "Successfully added 'glew'.")
  message(STATUS ${SECTION_SPLITTER})
  # GLFW
  message(STATUS "Adding 'glfw'...")
  FetchContent_Declare(glfw_project
                       SOURCE_DIR "${PROJECT_SOURCE_DIR}/glfw")
  message(STATUS "Successfully added 'glfw'.")

  set(GRAPHICS_LIBRARY "GL")
else () # Unknown
  message(FATAL_ERROR "Graphics library unknown.")
endif ()
message(STATUS ${SECTION_SPLITTER})
# spdlog
message(STATUS "Adding 'spdlog'...")
FetchContent_Declare(spdlog_project
                     SOURCE_DIR "${PROJECT_SOURCE_DIR}/spdlog")
message(STATUS "Successfully added 'spdlog'.")
message(STATUS ${SECTION_SPLITTER})
# OpenGL Mathematics
message(STATUS "Adding 'glm'...")
FetchContent_Declare(glm_project
                     SOURCE_DIR "${PROJECT_SOURCE_DIR}/glm")
message(STATUS "Successfully added 'glm'.")
message(STATUS ${SECTION_FOOTER})
