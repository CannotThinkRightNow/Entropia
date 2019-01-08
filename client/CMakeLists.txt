##################################################
# Client
##################################################

# Files
file (GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_executable (${PROJECT_NAME} ${CLIENT_SOURCE})
target_include_directories (${PROJECT_NAME} PUBLIC ${CLIENT_SOURCE})
target_link_libraries (${PROJECT_NAME} core)

# Packaging
install (TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${CLIENT_SOURCE} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PLATFORM}")
# Reinstall files from ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} to the directory of the executable to avoid missing libraries errors.
file (GLOB_RECURSE CMAKE_INSTALL_BIN CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/*")
file (INSTALL ${CMAKE_INSTALL_BIN} DESTINATION "${PROJECT_BINARY_DIR}/client")
