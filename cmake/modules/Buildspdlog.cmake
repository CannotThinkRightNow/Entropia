##################################################
# Build spdlog
##################################################

include(FindPackageHandleStandardArgs)

message(STATUS "Building spdlog...")

set(PROJECT_TEMP_DIR "${PROJECT_BINARY_DIR}/tmp")

set(spdlog_REPO_JSON "${PROJECT_TEMP_DIR}/spdlog/repo.json")
file(DOWNLOAD "https://api.github.com/repos/gabime/spdlog" ${spdlog_REPO_JSON} TLS_VERIFY ON)
file(READ ${spdlog_REPO_JSON} spdlog_DEFAULT_BRANCH)

string(REGEX MATCH "\"default_branch\": \"(.[^\"])+\"" spdlog_DEFAULT_BRANCH ${spdlog_DEFAULT_BRANCH})
string(REGEX MATCH " \".+\"" spdlog_DEFAULT_BRANCH ${spdlog_DEFAULT_BRANCH})
string(REPLACE " \"" "" spdlog_DEFAULT_BRANCH ${spdlog_DEFAULT_BRANCH})
string(REPLACE "\"" "" spdlog_DEFAULT_BRANCH ${spdlog_DEFAULT_BRANCH})

set(EXTERNALPROJECT_BUILD_NAME "spdlog")
set(EXTERNALPROJECT_BUILD_PREFIX "${PROJECT_BINARY_DIR}/external/${EXTERNALPROJECT_BUILD_NAME}")
set(EXTERNALPROJECT_BUILD_ARGS ${EXTERNALPROJECT_BUILD_NAME}_project GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
                                                                     GIT_TAG "origin/${spdlog_DEFAULT_BRANCH}"
                                                                     PREFIX "${EXTERNALPROJECT_BUILD_PREFIX}"
                                                                     CMAKE_ARGS -G "${CMAKE_GENERATOR}" ${PROJECT_ARGS} "-DCMAKE_INSTALL_PREFIX:PATH=${CONTRIB_DIR}" "-Dspdlog_BUILD_EXAMPLES:BOOL=${spdlog_BUILD_EXAMPLES}" "-Dspdlog_BUILD_BENCH:BOOL=${spdlog_BUILD_BENCH}" "-Dspdlog_BUILD_TESTS:BOOL=${spdlog_BUILD_TESTS}" "-Dspdlog_BUILD_HO_TESTS:BOOL=${spdlog_BUILD_HO_TESTS}" "-Dspdlog_SANITIZE_ADDRESS:BOOL=${spdlog_SANITIZE_ADDRESS}" "-Dspdlog_INSTALL:BOOL=${spdlog_INSTALL}" "-Dspdlog_FMT_EXTERNAL:BOOL=${spdlog_FMT_EXTERNAL}"
                                                                     GIT_SHALLOW TRUE
                                                                     GIT_PROGRESS TRUE)
include("${PROJECT_SOURCE_DIR}/cmake/ExternalProject_Build/invoke.cmake")
