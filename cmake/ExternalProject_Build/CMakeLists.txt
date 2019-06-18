##################################################
# ExternalProject Build
##################################################

cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})

project("ExternalProject Build")
include(ExternalProject)

ExternalProject_Add(${EXTERNALPROJECT_BUILD_ARGS})
