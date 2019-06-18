##################################################
# Build The OpenGL Extension Wrangler Library
##################################################

include(FindPackageHandleStandardArgs)

message(STATUS "Building GLEW...")

set(GLEW_DIR "${PROJECT_SOURCE_DIR}/glew")

file(READ "${GLEW_DIR}/README.md" GLEW_TGZ_URL)
set(PROJECT_TEMP_DIR "${PROJECT_BINARY_DIR}/tmp")
set(GLEW_SNAPSHOTS_TGZ "${PROJECT_TEMP_DIR}/GLEW/snapshots.html")
file(DOWNLOAD "https://sourceforge.net/projects/glew/files/glew/snapshots/" ${GLEW_SNAPSHOTS_TGZ} TLS_VERIFY ON)
file(READ ${GLEW_SNAPSHOTS_TGZ} GLEW_TGZ_SHA1)

# Assuming "${GLEW_DIR}/README.md" provides a download link.
string(REGEX MATCH "https:\/\/sourceforge.net\/projects\/glew\/files\/glew\/snapshots\/glew-[0-9]+\.tgz\/download" GLEW_TGZ_URL ${GLEW_TGZ_URL})
string(REGEX MATCH "glew-[0-9]+\.tgz" GLEW_TGZ_NAME ${GLEW_TGZ_URL})
  
string(REGEX MATCH "\"sha1\": \"[a-z0-9]+\", \"name\": \"${GLEW_TGZ_NAME}\"" GLEW_TGZ_SHA1 "${GLEW_TGZ_SHA1}")
string(REGEX MATCH "\"[a-z0-9]+\"," GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})
string(REPLACE "\"" "" GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})
string(REPLACE "," "" GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})

set(EXTERNALPROJECT_BUILD_NAME "glew")
set(EXTERNALPROJECT_BUILD_PREFIX "${PROJECT_BINARY_DIR}/external/${EXTERNALPROJECT_BUILD_NAME}")
set(EXTERNALPROJECT_BUILD_ARGS ${EXTERNALPROJECT_BUILD_NAME}_project URL ${GLEW_TGZ_URL} URL_HASH SHA1=${GLEW_TGZ_SHA1}
                                                                     SOURCE_SUBDIR "build/cmake"
                                                                     PREFIX "${EXTERNALPROJECT_BUILD_PREFIX}"
                                                                     CMAKE_ARGS -G ${CMAKE_GENERATOR} ${PROJECT_ARGS} "-DCMAKE_INSTALL_PREFIX:PATH=${CONTRIB_DIR}" "-DBUILD_UTILS:BOOL=${BUILD_UTILS}" "-DGLEW_REGAL:BOOL=${GLEW_REGAL}" "-DGLEW_OSMESA:BOOL=${GLEW_OSMESA}")
include("${PROJECT_SOURCE_DIR}/cmake/ExternalProject_Build/invoke.cmake")
