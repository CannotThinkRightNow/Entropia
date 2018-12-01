##################################################
# Application
##################################################\

# Files
if (ANDROID)
  # OpenGL ES 2.0
  find_library (GLES2_LIB "libGLESv2.so" HINTS "${ANDROID_NDK}/platforms/android-${CMAKE_ANDROID_API}/arch-${CMAKE_ANDROID_ARCH}")
  find_path (GLES2_INCLUDE_DIR "GLES2/gl2.h" HINTS ${ANDROID_NDK})
  set (GRAPHICS_LIBRARY "GLES2")
elseif (IOS)
  # TODO: use Metal here...
  set (GRAPHICS_LIBRARY "METAL")
else ()
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
  set (GLFW_BINARY_DIR "${PROJECT_BINARY_DIR}/glfw")

  set (GRAPHICS_LIBRARY "GL")
endif ()
message (STATUS "Graphics library: ${GRAPHICS_LIBRARY}")

configure_file ("src/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/out/config.h")
file (GLOB_RECURSE APPLICATION_OUT CONFIGURE_DEPENDS "out/*")
file (GLOB_RECURSE APPLICATION_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_executable (${PROJECT_NAME} ${APPLICATION_OUT} ${APPLICATION_SOURCE})
target_include_directories (${PROJECT_NAME} PUBLIC "out" PUBLIC "src")
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
  target_include_directories (${PROJECT_NAME} PUBLIC "${GLFW_DIR}/include")
endif ()
# Copy installed files from ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} to ${PROJECT_BINARY_DIR}/application to avoid missing libraries errors
file (GLOB_RECURSE CMAKE_INSTALL_BIN CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/*")
file (COPY ${CMAKE_INSTALL_BIN} DESTINATION "${PROJECT_BINARY_DIR}/application")

# Packaging
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${APPLICATION_OUT} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PLATFORM}")
install (FILES ${APPLICATION_SOURCE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
