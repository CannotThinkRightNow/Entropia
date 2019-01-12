##################################################
# GLEW
##################################################

set (GLEW_DIR "${PROJECT_SOURCE_DIR}/glew")
file (READ "${GLEW_DIR}/README.md" GLEW_TGZ_URL)

set (PROJECT_TEMP_DIR "${PROJECT_BINARY_DIR}/tmp")
set (GLEW_SNAPSHOTS_TGZ "${PROJECT_TEMP_DIR}/glew.html")
file (DOWNLOAD "https://sourceforge.net/projects/glew/files/glew/snapshots/" ${GLEW_SNAPSHOTS_TGZ} TLS_VERIFY ON)
file (READ ${GLEW_SNAPSHOTS_TGZ} GLEW_TGZ_SHA1)

string (REGEX MATCH "https:\/\/sourceforge.net\/projects\/glew\/files\/glew\/snapshots\/glew-[0-9]+\.tgz\/download" GLEW_TGZ_URL ${GLEW_TGZ_URL})
string (REGEX MATCH "glew-[0-9]+\.tgz" GLEW_TGZ_NAME ${GLEW_TGZ_URL})

string (REGEX MATCH "\"sha1\": \"[a-z0-9]+\", \"name\": \"${GLEW_TGZ_NAME}\"" GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})
string (REGEX MATCH "\"[a-z0-9]+\"," GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})
string (REPLACE "\"" "" GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})
string (REPLACE "," "" GLEW_TGZ_SHA1 ${GLEW_TGZ_SHA1})

string (REGEX MATCH "glew-[0-9]+\.tgz" GLEW_TGZ_NAME ${GLEW_TGZ_URL})
file (WRITE "${PROJECT_BINARY_DIR}/glew-0.tgz" "")
set (GLEW_TGZ "${PROJECT_TEMP_DIR}/${GLEW_TGZ_NAME}")
file (GLOB OLD_GLEW_TGZ "${PROJECT_BINARY_DIR}/glew-*.tgz")
if (NOT EXISTS ${GLEW_TGZ})
  message (STATUS "Downloading ${GLEW_TGZ_URL}...")
  file (DOWNLOAD ${GLEW_TGZ_URL} ${GLEW_TGZ} SHOW_PROGRESS EXPECTED_HASH SHA1=${GLEW_TGZ_SHA1} TLS_VERIFY ON)
  message (STATUS "Finished downloading ${GLEW_TGZ_URL}.")
else ()
  list (REMOVE_ITEM OLD_GLEW_TGZ ${GLEW_TGZ})
endif ()
file (REMOVE ${OLD_GLEW_TGZ})
set (GLEW_DIR "${PROJECT_BINARY_DIR}/glew")

if (NOT EXISTS ${GLEW_DIR})
  set (GLEW_TGZ_OUTPUT "${PROJECT_TEMP_DIR}/output")
  file (REMOVE_RECURSE ${GLEW_TGZ_OUTPUT})
  file (MAKE_DIRECTORY ${GLEW_TGZ_OUTPUT})
  message (STATUS "Unpacking ${GLEW_TGZ}...")
  execute_process (COMMAND ${CMAKE_COMMAND} -E tar -xf ${GLEW_TGZ} WORKING_DIRECTORY ${GLEW_TGZ_OUTPUT})
  message (STATUS "Finished unpacking ${GLEW_TGZ}.")
  file (GLOB GLEW_TGZ_OUTPUT "${GLEW_TGZ_OUTPUT}/glew-*")
  file (RENAME ${GLEW_TGZ_OUTPUT} "${PROJECT_BINARY_DIR}/glew")
endif ()

FetchContent_Declare (glew_project
                      SOURCE_DIR ${GLEW_DIR}
                      SOURCE_SUBDIR "build/cmake")
# Workaround
set (glew_project_SOURCE_SUBDIR "build/cmake")
