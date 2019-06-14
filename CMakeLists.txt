##################################################
# Unnamed
##################################################

# Policies
cmake_minimum_required(VERSION 3.12)

# Project
project("unnamed")

include("cmake/variables.cmake")
include("cmake/options.cmake")
include(GNUInstallDirs)
include(FetchContent)
include("cmake/gitmodules.cmake")
include("cmake/utilities.cmake")
include(GenerateExportHeader)

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

# Packaging
install(FILES "COPYING.txt" "COPYING.md" "LICENSE-LGPL-3.0.txt" "LICENSE-LGPL-3.0.md" "LICENSE-CC-BY-4.0.txt" ${OUT_INCLUDE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING.txt")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include(CPack)
