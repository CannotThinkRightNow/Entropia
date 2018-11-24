##################################################
# Unnamed
##################################################
# Press CMake > Cache (${name} Only) > Delete Cache Folders > CMakeLists.txt (or alternative if not in Microsoft Visual Studio) before building if changes are not picked up.

# Policies
cmake_minimum_required (VERSION 3.8)

# Project
project ("unnamed")

include(GNUInstallDirs)

# Variables
set (PROJECT_VERSION "0.0.1-b1-alpha")

string (FIND ${POLLY_TOOCHAIN_TAG} "android" ANDROID)
if (${ANDROID} EQUAL "-1")
  set (ANDROID FALSE)
else ()
  set (ANDROID TRUE)
endif ()
string (FIND ${POLLY_TOOCHAIN_TAG} "ios" IOS)
if (${IOS} EQUAL "-1")
  set (IOS FALSE)
else ()
  set (IOS TRUE)
endif ()
string (FIND ${POLLY_TOOCHAIN_TAG} "libcxx" LINUX)
if (${LINUX} EQUAL "-1")
  set (LINUX FALSE)
else ()
  set (LINUX TRUE)
endif ()
string (FIND ${POLLY_TOOCHAIN_TAG} "osx" MACOS)
if (${MACOS} EQUAL "-1")
  set (MACOS FALSE)
else ()
  set (MACOS TRUE)
endif ()
string (FIND ${POLLY_TOOCHAIN_TAG} "vs" WINDOWS)
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

# Sub-projects
add_subdirectory ("application")

# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include (CPack)
