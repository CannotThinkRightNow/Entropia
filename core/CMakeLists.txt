##################################################
# Core
##################################################

# Files
file(GLOB_RECURSE CORE_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CORE_INCLUDE_PUBLIC CONFIGURE_DEPENDS "include/public/*")

# Targets
add_library(core SHARED ${CORE_SOURCE})

# Generated files
generate_export_header(core EXPORT_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/include/public/${PROJECT_NAMESPACE}/core/export.h"
                            INCLUDE_GUARD_NAME "CORE_EXPORT_H_"
                            DEFINE_NO_DEPRECATED)
file(GLOB_RECURSE CORE_GENERATED_INCLUDE_PUBLIC CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/include/public/*")

# Targets (continued)
target_compile_definitions(core PUBLIC "GLFW_DLL")
set_target_properties(core PROPERTIES PUBLIC_HEADER "${CORE_INCLUDE_PUBLIC};${CORE_GENERATED_INCLUDE_PUBLIC}"
                                      PRIVATE_HEADER "${PROJECT_GENERATED_INCLUDE_PRIVATE}")
target_include_directories(core PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/public>" "$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/core/include/public>"
                                       "$<INSTALL_INTERFACE:${CORE_INSTALL_INCLUDEDIR}/core/public>"
                                PRIVATE "${PROJECT_BINARY_DIR}/include/private")

# Libraries
# Boost
target_link_libraries(core PUBLIC Boost::boost Boost::filesystem
                                  Boost::disable_autolinking) # Prevent Microsoft Visual Stuio auto-linking from overriding command-line arguments passed to the linker.
                                                              # https://stackoverflow.com/a/44133003/9341868
# Graphics
if (${GRAPHICS_LIBRARY} STREQUAL "GLES2") # OpenGL ES 2.0
  target_link_libraries(core PUBLIC gles2)
elseif (${GRAPHICS_LIBRARY} STREQUAL "METAL") # Metal
  # TODO: use Metal here...
elseif (${GRAPHICS_LIBRARY} STREQUAL "GL") # OpenGL
  # GLEW
  target_link_libraries(core PUBLIC GLEW::glew)
  # fix_glew_include_directory(core)
  # GLFW
  target_link_libraries(core PUBLIC glfw)
  # fix_glfw_include_directory(core)
endif () # Already checked.
# spdlog
target_link_libraries(core PUBLIC spdlog::spdlog)
# OpenGL Mathematics
target_link_libraries(core PUBLIC glm)

# Installation
install(TARGETS core
        EXPORT ${PROJECT_NAMESPACE}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/core/public"
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/core/private")

# Export
export(PACKAGE core)
