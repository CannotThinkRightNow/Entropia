##################################################
# Unnamed
##################################################

# Policies
cmake_minimum_required(VERSION 3.12)

# Project
include("cmake/utilities.cmake")
get_arguments(PROJECT_ARGS TRUE)

project("unnamed" VERSION 0.0.1.0
                  DESCRIPTION "No description given."
                  HOMEPAGE_URL "https://etaoinshrdlcumwfgypbvkjxqz.github.io/unnamed/"
                  LANGUAGES "C" "CXX")
set(PROJECT_VERSION_STRING "0.0.1.0-v1-alpha")
set(PROJECT_NAMESPACE "unnamed")

include("cmake/variables.cmake")
include("cmake/options.cmake")
include(GNUInstallDirs)
include(ExternalProject)
include(GenerateExportHeader)
include("cmake/patches.cmake")

# Git
Git_UpdateOrCheckSubmodules($ENV{CI})

# Dependencies
include("cmake/dependencies.cmake")

# Sub-projects
message(STATUS ${SECTION_HEADER})
message(STATUS "Building '${PROJECT_NAME}'...")

# Compile defintions
include("cmake/CompileDefinitions.cmake")

# Generated files
configure_file("include/private/config.h.in" "include/private/config.h" @ONLY)
file(GLOB_RECURSE PROJECT_GENERATED_INCLUDE_PRIVATE CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/include/private/*")

message(STATUS ${SECTION_SPLITTER})
# Core
message(STATUS "Building 'core'...")
add_subdirectory("core")
message(STATUS "Successfully built 'core'.")
message(STATUS ${SECTION_SPLITTER})
# Server
message(STATUS "Building 'server'...")
add_subdirectory("server")
message(STATUS "Successfully built 'server'.")
message(STATUS ${SECTION_SPLITTER})
# Client
message(STATUS "Building 'client'...")
add_subdirectory("client")
message(STATUS "Successfully built 'client'.")
message(STATUS ${SECTION_SPLITTER})
message(STATUS "Successfully built '${PROJECT_NAME}'.")
message(STATUS ${SECTION_FOOTER})

# Installation
install(FILES "COPYING.txt" "COPYING.md" "LICENSE-LGPL-3.0.txt" "LICENSE-LGPL-3.0.md" "LICENSE-CC-BY-4.0.txt"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(CMakePackageConfigHelpers)
set(VERSION_CONFIG_FILE "${PROJECT_BINARY_DIR}/${PROJECT_NAMESPACE}ConfigVersion.cmake")
write_basic_package_version_file(${VERSION_CONFIG_FILE} COMPATIBILITY SameMajorVersion)
install(FILES ${VERSION_CONFIG_FILE}
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAMESPACE}/cmake")

# Export
export(EXPORT ${PROJECT_NAMESPACE} NAMESPACE "${PROJECT_NAMESPACE}::")
install(EXPORT ${PROJECT_NAMESPACE} DESTINATION "${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAMESPACE}/cmake"
                                    NAMESPACE "${PROJECT_NAMESPACE}::")

# Uninstallation
# if (NOT TARGET uninstall)
#   configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)
#   add_custom_target(uninstall COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")
# endif ()

# Packaging
include("cmake/packaging.cmake")
