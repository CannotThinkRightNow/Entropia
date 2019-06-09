##################################################
# Core
##################################################

# Files
configure_file("include/core/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/include/core/config.h" @ONLY)
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CORE_INCLUDE CONFIGURE_DEPENDS "include/*")
set(CORE_EXPORT_HEADER "${CMAKE_CURRENT_LIST_DIR}/include/core/core_export.h")

# Targets
add_library(core SHARED ${CORE_SOURCE})
generate_export_header(core EXPORT_FILE_NAME ${CORE_EXPORT_HEADER}
                            INCLUDE_GUARD_NAME "CORE_EXPORT_H_"
                            DEFINE_NO_DEPRECATED)
set_target_properties(core PROPERTIES PUBLIC_HEADER "${CORE_INCLUDE}"
                                      PRIVATE_HEADER "${CORE_EXPORT_HEADER}")
target_include_directories(core PUBLIC "include")

# Libraries
# Boost
target_link_libraries(core Boost::boost Boost::filesystem)
# Graphics
if (${GRAPHICS_LIBRARY} STREQUAL "GLES2") # OpenGL ES 2.0
  target_link_libraries(core gles2)
elseif (${GRAPHICS_LIBRARY} STREQUAL "METAL") # Metal
  # TODO: use Metal here...
elseif (${GRAPHICS_LIBRARY} STREQUAL "GL") # OpenGL
  # GLEW
  FetchContent_CheckAndPopulate(glew_project)
  target_link_libraries(core glew)
  FetchContent_GetProperties(glew_project)
  target_include_directories(core PUBLIC "${glew_project_SOURCE_DIR}/include")
  # GLFW
  FetchContent_CheckAndPopulate(glfw_project)
  target_link_libraries(core glfw)
endif () # Already checked.
# spdlog
FetchContent_CheckAndPopulate(spdlog_project)
target_link_libraries(core spdlog)

# Packaging
set(CORE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/core")
install(TARGETS core
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CORE_INSTALL_INCLUDEDIR}
        PRIVATE_HEADER DESTINATION ${CORE_INSTALL_INCLUDEDIR})
