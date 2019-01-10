##################################################
# Unnamed
##################################################

# Policies
cmake_minimum_required (VERSION 3.12)

# Project
project ("unnamed")

# Variables
set (SECTION_HEADER "==================================================")
set (SECTION_SPLITTER "--------------------------------------------------")
set (SECTION_FOOTER "==================================================")

include(GNUInstallDirs)
set (PROJECT_VERSION "0.0.1-v1-alpha")

if (NOT DEFINED TOOLCHAIN_TAG)
  if (DEFINED CMAKE_TOOLCHAIN_FILE)
    set (TOOLCHAIN_TAG ${CMAKE_TOOLCHAIN_FILE})
  else ()
    message (FATAL_ERROR "CMAKE_TOOLCHAIN_FILE and TOOLCHAIN_TAG are not defined.")
  endif ()
endif ()

string (FIND ${TOOLCHAIN_TAG} "android" ANDROID)
if (${ANDROID} EQUAL "-1")
  set (ANDROID FALSE)
else ()
  set (ANDROID TRUE)
endif ()
string (FIND ${TOOLCHAIN_TAG} "ios" IOS)
if (${IOS} EQUAL "-1")
  set (IOS FALSE)
else ()
  set (IOS TRUE)
endif ()
string (FIND ${TOOLCHAIN_TAG} "libcxx" LINUX)
if (${LINUX} EQUAL "-1")
  set (LINUX FALSE)
else ()
  set (LINUX TRUE)
endif ()
string (FIND ${TOOLCHAIN_TAG} "osx" MACOS)
if (${MACOS} EQUAL "-1")
  set (MACOS FALSE)
else ()
  set (MACOS TRUE)
endif ()
string (FIND ${TOOLCHAIN_TAG} "vs" WINDOWS)
if (${WINDOWS} EQUAL "-1")
  set (WINDOWS FALSE)
else ()
  set (WINDOWS TRUE)
endif ()

if (ANDROID)
  set (PLATFORM "ANDROID")
elseif (IOS)
  set (PLATFORM "IOS")
elseif (LINUX)
  set (PLATFORM "LINUX")
elseif (MACOS)
  set (PLATFORM "MACOS")
else (WINDOWS)
  set (PLATFORM "WINDOWS")
endif ()

if (WINDOWS)
  set (SECURE_FUNCTIONS 1)
else ()
  set (SECURE_FUNCTIONS 0)
endif ()

if (NOT DEFINED ENV{CI})
  set (ENV{CI} FALSE)
elseif ($ENV{CI} EQUAL "true" # Travis CI, AppVeyor
        OR $ENV{CI} EQUAL "True") # AppVeyor
  set (ENV{CI} TRUE)
endif ()

message (STATUS ${SECTION_HEADER})
message (STATUS "Variables")
message (STATUS ${SECTION_SPLITTER})
message (STATUS "Name: ${PROJECT_NAME}")
message (STATUS "Version: ${PROJECT_VERSION}")
message (STATUS "Toolchain: ${TOOLCHAIN_TAG}")
message (STATUS "Platform: ${PLATFORM}")
message (STATUS "Continuous Integration: $ENV{CI}")
message (STATUS ${SECTION_FOOTER})

# Files
# Submodules
message (STATUS ${SECTION_HEADER})
message (STATUS "Submodules")
file (STRINGS ".gitmodules" GIT_SUBMODULES_FILE)
foreach (GIT_SUBMODULE_LINE ${GIT_SUBMODULES_FILE})
  string (FIND ${GIT_SUBMODULE_LINE} "[" GIT_SUBMODULE_START)
  if (${GIT_SUBMODULE_START} EQUAL "-1")
    set (GIT_SUBMODULE_START FALSE)
  else ()
    set (GIT_SUBMODULE_START TRUE)
  endif ()
  if (GIT_SUBMODULE_START)
    list (APPEND GIT_SUBMODULES ${GIT_SUBMODULE})
    set (GIT_SUBMODULE "${GIT_SUBMODULE_LINE}\n")
  else ()
    string (APPEND GIT_SUBMODULE "${GIT_SUBMODULE_LINE}\n")
  endif ()
endforeach (${GIT_SUBMODULE_LINE})
list (APPEND GIT_SUBMODULES ${GIT_SUBMODULE})
unset (GIT_SUBMODULE)
foreach (GIT_SUBMODULE ${GIT_SUBMODULES})
  message (STATUS ${SECTION_SPLITTER})
  # Name
  string (REGEX MATCH "\".+\"" GIT_SUBMODULE_NAME ${GIT_SUBMODULE})
  string (REPLACE "\"" "" GIT_SUBMODULE_NAME ${GIT_SUBMODULE_NAME})
  message (STATUS "Name: ${GIT_SUBMODULE_NAME}")
  # Path
  string (REGEX MATCH "path = .+" GIT_SUBMODULE_PATH ${GIT_SUBMODULE})
  string (REGEX REPLACE "path[ ]*=[ ]*" "" GIT_SUBMODULE_PATH ${GIT_SUBMODULE_PATH})
  string (REGEX REPLACE "\n.+" "" GIT_SUBMODULE_PATH ${GIT_SUBMODULE_PATH})
  set (GIT_SUBMODULE_PATH "${PROJECT_SOURCE_DIR}/${GIT_SUBMODULE_PATH}")
  message (STATUS "Path: ${GIT_SUBMODULE_PATH}")
  # Fetch
  execute_process (COMMAND git symbolic-ref refs/remotes/origin/HEAD WORKING_DIRECTORY ${GIT_SUBMODULE_PATH} OUTPUT_VARIABLE GIT_DEFAULT_BRANCH)
  string (REPLACE "refs/remotes/origin/" "" GIT_DEFAULT_BRANCH ${GIT_DEFAULT_BRANCH})
  string (REPLACE "\n" "" GIT_DEFAULT_BRANCH ${GIT_DEFAULT_BRANCH})
  execute_process (COMMAND git checkout ${GIT_DEFAULT_BRANCH} WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
  execute_process (COMMAND git fetch WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
  # Check
  if (ENV{CI})
    message (STATUS "Checking '${GIT_SUBMODULE_NAME}'...")
    execute_process (COMMAND git status WORKING_DIRECTORY ${GIT_SUBMODULE_PATH} OUTPUT_VARIABLE GIT_SUBMODULE_UPDATED)
    string (FIND ${GIT_SUBMODULE_UPDATED} "up to date" GIT_SUBMODULE_UPDATED)
    if (${GIT_SUBMODULE_UPDATED} EQUAL "-1")
      message (FATAL_ERROR "Outdated or modified '${GIT_SUBMODULE_NAME}' detected.")
    endif ()
    message (STATUS "Updated '${GIT_SUBMODULE_NAME}' detected.")
  # Update
  else ()
    message (STATUS "Updating '${GIT_SUBMODULE_NAME}'...")
    execute_process (COMMAND git pull WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
    execute_process (COMMAND git add ${GIT_SUBMODULE_NAME} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
    message (STATUS "Finished updating '${GIT_SUBMODULE_NAME}'.")
  endif ()
endforeach (${GIT_SUBMODULE})
message (STATUS ${SECTION_FOOTER})

# Dependencies
# Files
message (STATUS ${SECTION_HEADER})
message (STATUS "Dependencies")
message (STATUS ${SECTION_SPLITTER})
if (ANDROID)
  # OpenGL ES 2.0
  find_library (GLES2_LIB "libGLESv2.so" HINTS "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}")
  find_path (GLES2_INCLUDE "GLES2/gl2.h" HINTS ${ANDROID_NDK})

  set (GRAPHICS_LIBRARY "GLES2")
elseif (IOS)
  # TODO: use Metal here...

  set (GRAPHICS_LIBRARY "METAL")
elseif (LINUX OR MACOS OR WINDOWS)
  # GLEW
  set (GLEW_DIR "${PROJECT_SOURCE_DIR}/glew")
  file (READ "${GLEW_DIR}/README.md" GLEW_TGZ_URL)
  string (REGEX MATCH "https:\/\/sourceforge.net\/projects\/glew\/files\/glew\/snapshots\/glew-[0-9]+\.tgz\/download" GLEW_TGZ_URL ${GLEW_TGZ_URL})
  string (REGEX MATCH "glew-[0-9]+\.tgz" GLEW_TGZ_NAME ${GLEW_TGZ_URL})
  file (WRITE "${PROJECT_BINARY_DIR}/glew-0.tgz" "")
  set (GLEW_TGZ "${PROJECT_BINARY_DIR}/${GLEW_TGZ_NAME}")
  file (GLOB OLD_GLEW_TGZ "${PROJECT_BINARY_DIR}/glew-*.tgz")
  if (NOT EXISTS ${GLEW_TGZ})
    message (STATUS "Downloading ${GLEW_TGZ_URL}...")
    file (DOWNLOAD ${GLEW_TGZ_URL} ${GLEW_TGZ} SHOW_PROGRESS TLS_VERIFY ON)
    message (STATUS "Finished downloading ${GLEW_TGZ_URL}.")
    set (GLEW_TGZ_OUTPUT_DIR "${PROJECT_BINARY_DIR}/output")
    file (REMOVE_RECURSE ${GLEW_TGZ_OUTPUT_DIR})
    file (MAKE_DIRECTORY ${GLEW_TGZ_OUTPUT_DIR})
    message (STATUS "Unpacking ${GLEW_TGZ}...")
    execute_process (COMMAND ${CMAKE_COMMAND} -E tar -xf ${GLEW_TGZ} WORKING_DIRECTORY ${GLEW_TGZ_OUTPUT_DIR})
    message (STATUS "Finished unpacking ${GLEW_TGZ}.")
    file (GLOB GLEW_DIR "${PROJECT_BINARY_DIR}/output/glew-*")
    file (RENAME ${GLEW_DIR} "${PROJECT_BINARY_DIR}/glew")
  else ()
    list (REMOVE_ITEM OLD_GLEW_TGZ ${GLEW_TGZ})
  endif ()
  set (GLEW_DIR "${PROJECT_BINARY_DIR}/glew")
  file (REMOVE ${OLD_GLEW_TGZ})
  # GLFW
  set (GLFW_DIR "${PROJECT_SOURCE_DIR}/glfw")

  set (GRAPHICS_LIBRARY "GL")
endif ()
message (STATUS "Graphics library: ${GRAPHICS_LIBRARY}")
# spdlog
set (SPDLOG_DIR "${PROJECT_SOURCE_DIR}/spdlog")
# Build
# Boost
message (STATUS ${SECTION_SPLITTER})
message (STATUS "Building 'boost'...")
add_subdirectory ("boost")
message (STATUS "Successfully built 'boost'.")
if (${GRAPHICS_LIBRARY} STREQUAL "METAL") # Metal
  # TODO: use Metal here...
elseif (${GRAPHICS_LIBRARY} STREQUAL "GL") # OpenGL
  # GLEW
  message (STATUS ${SECTION_SPLITTER})
  message (STATUS "Building 'glew'...")
  add_subdirectory ("${GLEW_DIR}/build/cmake" ${GLEW_DIR})
  message (STATUS "Successfully built 'glew'.")
  # GLFW
  message (STATUS ${SECTION_SPLITTER})
  message (STATUS "Building 'glfw'...")
  add_subdirectory (${GLFW_DIR})
  message (STATUS "Successfully built 'glfw'.")
else ()
  message (FATAL_ERROR "Unknown graphics library: ${GRAPHICS_LIBRARY}")
endif ()
# spdlog
message (STATUS ${SECTION_SPLITTER})
message (STATUS "Building 'spdlog'...")
add_subdirectory (${SPDLOG_DIR})
message (STATUS "Successfully built 'spdlog'.")
message (STATUS ${SECTION_FOOTER})

# Sub-projects
message (STATUS ${SECTION_HEADER})
message (STATUS "Building '${PROJECT_NAME}'...")
message (STATUS ${SECTION_SPLITTER})
# Core
message (STATUS "Building 'core'...")
add_subdirectory ("core")
message (STATUS "Successfully built 'core'.")
message (STATUS ${SECTION_SPLITTER})
# Server
message (STATUS "Building 'server'...")
add_subdirectory ("server")
message (STATUS "Successfully built 'server'.")
message (STATUS ${SECTION_SPLITTER})
# Client
message (STATUS "Building 'client'...")
add_subdirectory ("client")
message (STATUS "Successfully built 'client'.")
message (STATUS ${SECTION_SPLITTER})
message (STATUS "Successfully built '${PROJECT_NAME}'.")
message (STATUS ${SECTION_FOOTER})

# Packaging
install (FILES "LICENSE.txt" "LICENSE.md" DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE.txt")
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include (CPack)
