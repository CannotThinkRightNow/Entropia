##################################################
# Build Graphics Library Framework
##################################################

include(FindPackageHandleStandardArgs)

message(STATUS "Building GLFW...")

set(PROJECT_TEMP_DIR "${PROJECT_BINARY_DIR}/tmp")

set(GLFW_REPO_JSON "${PROJECT_TEMP_DIR}/glfw/repo.json")
file(DOWNLOAD "https://api.github.com/repos/glfw/glfw" ${GLFW_REPO_JSON} TLS_VERIFY ON)
file(READ ${GLFW_REPO_JSON} GLFW_DEFAULT_BRANCH)

string(REGEX MATCH "\"default_branch\": \"(.[^\"])+\"" GLFW_DEFAULT_BRANCH ${GLFW_DEFAULT_BRANCH})
string(REGEX MATCH " \".+\"" GLFW_DEFAULT_BRANCH ${GLFW_DEFAULT_BRANCH})
string(REPLACE " \"" "" GLFW_DEFAULT_BRANCH ${GLFW_DEFAULT_BRANCH})
string(REPLACE "\"" "" GLFW_DEFAULT_BRANCH ${GLFW_DEFAULT_BRANCH})

set(EXTERNALPROJECT_BUILD_NAME "glfw")
set(EXTERNALPROJECT_BUILD_PREFIX "${PROJECT_BINARY_DIR}/external/${EXTERNALPROJECT_BUILD_NAME}")
set(EXTERNALPROJECT_BUILD_CONFIG_ARGS "-Wno-dev -Wno-error=dev -Wno-error=deprecated")
set(EXTERNALPROJECT_BUILD_ARGS ${EXTERNALPROJECT_BUILD_NAME}_project GIT_REPOSITORY "https://github.com/glfw/glfw.git"
                                                                     GIT_TAG "origin/${GLFW_DEFAULT_BRANCH}"
                                                                     PREFIX "${EXTERNALPROJECT_BUILD_PREFIX}"
                                                                     CMAKE_ARGS -G "${CMAKE_GENERATOR}" ${PROJECT_ARGS} "-DCMAKE_INSTALL_PREFIX:PATH=${CONTRIB_DIR}" "-DBUILD_SHARED_LIBS:BOOL=${BUILD_SHARED_LIBS}" "-DGLFW_BUILD_EXAMPLES:BOOL=${GLFW_BUILD_EXAMPLES}" "-DGLFW_BUILD_TESTS:BOOL=${GLFW_BUILD_TESTS}" "-DGLFW_BUILD_DOCS:BOOL=${GLFW_BUILD_DOCS}" "-DGLFW_INSTALL:BOOL=${GLFW_INSTALL}" "-DGLFW_VULKAN_STATIC:BOOL=${GLFW_VULKAN_STATIC}"
                                                                     BUILD_COMMAND ${CMAKE_COMMAND} --build "${EXTERNALPROJECT_BUILD_PREFIX}" --config "${CMAKE_BUILD_TYPE}"
                                                                     GIT_SHALLOW TRUE
                                                                     GIT_PROGRESS TRUE)
include("${PROJECT_SOURCE_DIR}/cmake/ExternalProject_Build/invoke.cmake")
