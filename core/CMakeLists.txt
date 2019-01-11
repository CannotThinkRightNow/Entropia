##################################################
# Core
##################################################\

# Files
configure_file ("src/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/out/config.h")
file (GLOB_RECURSE APPLICATION_OUT CONFIGURE_DEPENDS "out/*")
file (GLOB_RECURSE APPLICATION_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_library (core ${APPLICATION_OUT} ${APPLICATION_SOURCE})
target_include_directories (core PUBLIC "out" PUBLIC "src")
# Boost
# Filesystem
target_link_libraries (core boost_filesystem)
if (${GRAPHICS_LIBRARY} STREQUAL "GLES2") # OpenGL ES 2.0
  target_link_libraries (core gles2)
elseif (${GRAPHICS_LIBRARY} STREQUAL "METAL") # Metal
  # TODO: use Metal here...
elseif (${GRAPHICS_LIBRARY} STREQUAL "GL") # OpenGL
  # GLEW
  target_link_libraries (core glew)
  # GLFW
  target_link_libraries (core glfw)
endif () # Already checked.
# spdlog
target_link_libraries (core spdlog)

# Packaging
install (TARGETS core DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${APPLICATION_OUT} ${APPLICATION_SOURCE} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PLATFORM}")
