##################################################
# Application
##################################################
# Policies
cmake_minimum_required (VERSION 3.8)

# Files
configure_file ("src/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/src/config.h")
aux_source_directory ("src" APPLICATION_SOURCE)

if (ANDROID)
  # OpenGL ES 2.0
  find_library (GLES2_LIB "libGLESv2.so" HINTS "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}")
  find_path (GLES2_INCLUDE_DIR "GLES2/gl2.h" HINTS ${ANDROID_NDK})
elseif (IOS)
  # TODO: use Metal here...
else ()
  # GLEW
  set (GLEW_DIR "${PROJECT_SOURCE_DIR}/glew")
  file (READ "${GLEW_DIR}/README.md" GLEW_SOURCE_TGZ_URL)
  string (REGEX MATCH "https:\/\/sourceforge.net\/projects\/glew\/files\/glew\/snapshots\/glew-[0-9]+\.tgz\/download" GLEW_SOURCE_TGZ_URL ${GLEW_SOURCE_TGZ_URL})
  string (REGEX MATCH "glew-[0-9]+\.tgz" GLEW_SOURCE_TGZ_NAME ${GLEW_SOURCE_TGZ_URL})
  file (WRITE "${PROJECT_BINARY_DIR}/glew-0.tgz" "")
  set (GLEW_SOURCE_TGZ_PATH "${PROJECT_BINARY_DIR}/${GLEW_SOURCE_TGZ_NAME}")
  file (GLOB OLD_GLEW_SOURCE_TGZ_NAMES "${PROJECT_BINARY_DIR}/glew-*.tgz")
  if (NOT EXISTS ${GLEW_SOURCE_TGZ_PATH})
    file (DOWNLOAD ${GLEW_SOURCE_TGZ_URL} ${GLEW_SOURCE_TGZ_PATH} SHOW_PROGRESS TLS_VERIFY ON)
    execute_process (COMMAND ${CMAKE_COMMAND} -E remove_directory "output")
    execute_process (COMMAND ${CMAKE_COMMAND} -E make_directory "output")
    execute_process (COMMAND ${CMAKE_COMMAND} -E chdir "output" ${CMAKE_COMMAND} -E tar -xvf "${GLEW_SOURCE_TGZ_PATH}" WORKING_DIRECTORY "${PROJECT_BINARY_DIR}")
    file (GLOB GLEW_DIR "${PROJECT_BINARY_DIR}/output/glew-*/")
    file (RENAME ${GLEW_DIR} "${PROJECT_BINARY_DIR}/glew/")
  else ()
    list (REMOVE_ITEM OLD_GLEW_SOURCE_TGZ_NAMES ${GLEW_SOURCE_TGZ_PATH})
  endif ()
  set (GLEW_DIR "${PROJECT_BINARY_DIR}/glew/")
  file (REMOVE ${OLD_GLEW_SOURCE_TGZ_NAMES})
  # GLFW
  set (GLFW_DIR "${PROJECT_SOURCE_DIR}/glfw")
  set (GLFW_BINARY_DIR "${PROJECT_BINARY_DIR}/glfw")
endif ()

# Target definitions
add_executable (${PROJECT_NAME} ${APPLICATION_SOURCE})
if (ANDROID)
  # OpenGL ES 2.0
  target_link_libraries (${PROJECT_NAME} ${GLES2_LIB})
  target_include_directories (${PROJECT_NAME} PUBLIC ${GLES2_INCLUDE_DIR})
elseif (IOS)
  # TODO: use Metal here...
else ()
  # GLEW
  add_subdirectory ("${GLEW_DIR}/build/cmake" ${GLEW_DIR})
  target_link_libraries (${PROJECT_NAME} glew)
  target_include_directories (${PROJECT_NAME} PUBLIC "${GLEW_DIR}/include")
  # GLFW
  add_subdirectory (${GLFW_DIR} ${GLFW_BINARY_DIR})
  target_link_libraries (${PROJECT_NAME} glfw)
endif ()

# Packaging
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${APPLICATION_SOURCE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
