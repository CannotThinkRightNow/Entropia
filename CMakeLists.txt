##################################################
# Unnamed
##################################################
# Press CMake > Cache (${name} Only) > Delete Cache Folders > CMakeLists.txt (or alternative if not in Microsoft Visual Studio) before building if changes are made.

# Policies
cmake_minimum_required (VERSION 3.8)

# Project
project ("unnamed")

# Variables
set (PROJECT_VERSION "0.0.1-b1-alpha")
if (NOT DEFINED POLLY_TOOLCHAIN_TAG)
  set (POLLY_TOOLCHAIN_TAG " ")
endif ()
string (FIND ${POLLY_TOOLCHAIN_TAG} "android" ANDROID)
if (${ANDROID} EQUAL "-1")
  set (ANDROID FALSE)
else ()
  set (ANDROID TRUE)
endif ()
string (FIND ${POLLY_TOOLCHAIN_TAG} "ios" IOS)
if (${IOS} EQUAL "-1")
  set (IOS FALSE)
else ()
  set (IOS TRUE)
endif ()

# Sub-projects
add_subdirectory ("application")

# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_NAME ${PROJECT_NAME})
set (CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
include (CPack)
