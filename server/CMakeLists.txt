##################################################
# Server
##################################################

# Files
file (GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_executable (server ${SERVER_SOURCE})
target_link_libraries (server core)

# Packaging
# Reinstall files from ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} to the directory of the executable to avoid missing libraries errors.
# file (GLOB_RECURSE CMAKE_INSTALL_BIN CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/*")
# file (INSTALL ${CMAKE_INSTALL_BIN} DESTINATION "${PROJECT_BINARY_DIR}/server")
install (TARGETS server DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${SERVER_SOURCE} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
