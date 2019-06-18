##################################################
# Dependencies
##################################################

message(STATUS ${SECTION_HEADER})
message(STATUS "Dependencies")
message(STATUS ${SECTION_SPLITTER})
# Boost
message(STATUS "Finding Boost...")
find_package(Boost ${Boost_MINIMUM_VERSION} REQUIRED COMPONENTS ${Boost_COMPONENTS})
message(STATUS ${SECTION_SPLITTER})

# Graphics
if (ANDROID) # OpenGL ES 2.0
  find_package(GLES2 REQUIRED) # OpenGL ES 2.0
  message(STATUS ${SECTION_SPLITTER})
  set(GRAPHICS_LIBRARY "GLES2")
elseif (IOS) # Metal
  # TODO: use Metal here...
  set(GRAPHICS_LIBRARY "METAL")
elseif (UNIX OR MACOS OR WINDOWS) # OpenGL
   # GLEW
  include(BuildGLEW)
  find_package(glew REQUIRED CONFIG PATHS "${CONTRIB_DIR}/lib/cmake/glew" NO_DEFAULT_PATH)
  message(STATUS ${SECTION_SPLITTER})
  # GLFW
  include(BuildGLFW)
  find_package(glfw3 REQUIRED CONFIG PATHS "${CONTRIB_DIR}/lib/cmake/glfw3" NO_DEFAULT_PATH)
  set(GRAPHICS_LIBRARY "GL")
else () # Unknown
  message(FATAL_ERROR "Graphics library unknown.")
endif ()
message(STATUS ${SECTION_SPLITTER})
# spdlog
include(Buildspdlog)
find_package(spdlog REQUIRED CONFIG PATHS "${CONTRIB_DIR}/lib/spdlog/cmake" NO_DEFAULT_PATH)
message(STATUS ${SECTION_SPLITTER})
# OpenGL Mathematics
include(BuildGLM)
find_package(glm REQUIRED CONFIG PATHS "${CONTRIB_DIR}/lib/cmake/glm" NO_DEFAULT_PATH)
message(STATUS ${SECTION_FOOTER})

# File manipulation
file(COPY "${CONTRIB_DIR}" DESTINATION "${PROJECT_BINARY_DIR}")
install(DIRECTORY "${CONTRIB_DIR}/" DESTINATION "${CMAKE_INSTALL_PREFIX}")
