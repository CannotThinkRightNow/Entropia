##################################################
# Core
##################################################

# Files
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CORE_INCLUDE_PUBLIC CONFIGURE_DEPENDS "include/public/*")

# Targets
add_library(core SHARED ${CORE_SOURCE})

# Generated files
generate_export_header(core EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/core/include/public/${PROJECT_NAMESPACE}/core/export.h"
                            INCLUDE_GUARD_NAME "CORE_EXPORT_H_"
                            DEFINE_NO_DEPRECATED)
file(GLOB_RECURSE CORE_GENERATED_INCLUDE_PUBLIC CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/include/public/*")

# Targets (continued)
set_target_properties(core PROPERTIES PUBLIC_HEADER "${CORE_INCLUDE_PUBLIC};${CORE_GENERATED_INCLUDE_PUBLIC}"
                                      PRIVATE_HEADER "${PROJECT_GENERATED_INCLUDE_PRIVATE}"
                                      COMPILE_DEFINITIONS "GLFW_DLL")
target_include_directories(core PUBLIC "include/public" "${PROJECT_BINARY_DIR}/core/include/public"
                                PRIVATE "${PROJECT_BINARY_DIR}/include/private")

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
# OpenGL Mathematics
FetchContent_CheckAndPopulate(glm_project)
target_link_libraries(core glm)

# Packaging
set(CORE_INSTALL_INCLUDEDIR "${CMAKE_INSTALL_INCLUDEDIR}/core")
install(TARGETS core
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION "${CORE_INSTALL_INCLUDEDIR}/core/public"
        PRIVATE_HEADER DESTINATION "${CORE_INSTALL_INCLUDEDIR}/core/private")
