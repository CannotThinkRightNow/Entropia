##################################################
# Core
##################################################\

# Files
configure_file ("include/core/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/include/core/config.h" @ONLY)
file (GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS "src/*")
file (GLOB_RECURSE CORE_INCLUDE CONFIGURE_DEPENDS "include/*")

# Targets
add_library (core ${CORE_SOURCE})
target_include_directories (core PUBLIC "include")
if (${GRAPHICS_LIBRARY} STREQUAL "GLES2") # OpenGL ES 2.0
  target_link_libraries (core gles2)
elseif (${GRAPHICS_LIBRARY} STREQUAL "METAL") # Metal
  # TODO: use Metal here...
elseif (${GRAPHICS_LIBRARY} STREQUAL "GL") # OpenGL
  # GLEW
  FetchContent_CheckAndPopulate (glew_project)
  target_link_libraries (core glew)
  # GLFW
  FetchContent_CheckAndPopulate (glfw_project)
  target_link_libraries (core glfw)
endif () # Already checked.
# spdlog
FetchContent_CheckAndPopulate (spdlog_project)
target_link_libraries (core spdlog)

# Packaging
install (TARGETS core DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${CORE_SOURCE} ${CORE_INCLUDE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
