##################################################
# Core
##################################################

# Files
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CORE_INCLUDE CONFIGURE_DEPENDS "include/*")
set(CONFIG_HEADER "${CMAKE_CURRENT_LIST_DIR}/include/config.h")
configure_file("include/config.h.in" ${CONFIG_HEADER} @ONLY)
set(CORE_EXPORT_HEADER "${CMAKE_CURRENT_LIST_DIR}/include/${PROJECT_NAMESPACE}/core/export.h")
list(REMOVE_ITEM CORE_INCLUDE ${CONFIG_HEADER} ${CORE_EXPORT_HEADER})

# Targets
add_library(core SHARED ${CORE_SOURCE})
generate_export_header(core EXPORT_FILE_NAME ${CORE_EXPORT_HEADER}
                            INCLUDE_GUARD_NAME "CORE_EXPORT_H_"
                            DEFINE_NO_DEPRECATED)
get_target_property(CORE_COMPILE_DEFINITIONS core COMPILE_DEFINITIONS)
if (NOT ${CORE_COMPILE_DEFINITIONS})
  set(CORE_COMPILE_DEFINITIONS "")
endif ()
set_target_properties(core PROPERTIES PUBLIC_HEADER "${CORE_INCLUDE}"
                                      PRIVATE_HEADER "${CONFIG_HEADER};${CORE_EXPORT_HEADER}"
                                      COMPILE_DEFINITIONS "GLFW_DLL;${CORE_COMPILE_DEFINITIONS}")
target_include_directories(core PUBLIC "include")

# Libraries
# Boost
target_link_libraries(core Boost::boost Boost::filesystem
                           Boost::disable_autolinking) # Prevent Microsoft Visual Stuio auto-linking from overriding command-line arguments passed to the linker.
                                                       # https://stackoverflow.com/a/44133003/9341868
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
