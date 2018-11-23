##################################################
# Application
##################################################
# Policies
cmake_minimum_required (VERSION 3.8)

# Files
configure_file ("src/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/src/config.h")
aux_source_directory ("src" APPLICATION_SOURCE)

set (GLEW_DIR "${PROJECT_SOURCE_DIR}/glew")
file (READ "${GLEW_DIR}/README.md" GLEW_SOURCE_TGZ_URL)
string (REGEX MATCH "https:\/\/sourceforge.net\/projects\/glew\/files\/glew\/snapshots\/glew-[0-9]+\.tgz\/download" GLEW_SOURCE_TGZ_URL ${GLEW_SOURCE_TGZ_URL})
string (REGEX MATCH "glew-[0-9]+\.tgz" GLEW_SOURCE_TGZ_NAME ${GLEW_SOURCE_TGZ_URL})
set (GLEW_SOURCE_PATH "${PROJECT_BINARY_DIR}/glew")
file (WRITE "${GLEW_SOURCE_PATH}/glew-0.tgz" "")
set (GLEW_SOURCE_TGZ_PATH "${GLEW_SOURCE_PATH}/${GLEW_SOURCE_TGZ_NAME}")
file (GLOB OLD_GLEW_SOURCE_TGZ_NAMES "${GLEW_SOURCE_PATH}/glew-*.tgz")
if (NOT EXISTS ${GLEW_SOURCE_TGZ_PATH})
  file (DOWNLOAD ${GLEW_SOURCE_TGZ_URL} ${GLEW_SOURCE_TGZ_PATH} SHOW_PROGRESS TLS_VERIFY ON)
  execute_process (COMMAND ${CMAKE_COMMAND} -E remove_directory "output"
                   WORKING_DIRECTORY "${GLEW_SOURCE_PATH}")
  execute_process (COMMAND ${CMAKE_COMMAND} -E make_directory "output"
                   WORKING_DIRECTORY "${GLEW_SOURCE_PATH}")
  execute_process (COMMAND ${CMAKE_COMMAND} -E chdir "output" ${CMAKE_COMMAND} -E tar -xvf "${GLEW_SOURCE_TGZ_PATH}"
                   WORKING_DIRECTORY "${GLEW_SOURCE_PATH}")
else ()
  list (REMOVE_ITEM OLD_GLEW_SOURCE_TGZ_NAMES ${GLEW_SOURCE_TGZ_PATH})
endif ()
file (REMOVE ${OLD_GLEW_SOURCE_TGZ_NAMES})
file (GLOB GLEW_DIR "${GLEW_SOURCE_PATH}/output/glew-*/")

# Target definitions
add_executable (${PROJECT_NAME} ${APPLICATION_SOURCE})
add_subdirectory ("${GLEW_DIR}/build/cmake" "${GLEW_DIR}/build")
target_link_libraries (${PROJECT_NAME} glew)
include_directories ("${GLEW_DIR}/include")

# Packaging
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
install (FILES ${APPLICATION_SOURCE} DESTINATION include)
