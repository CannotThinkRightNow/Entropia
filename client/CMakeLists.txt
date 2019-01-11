##################################################
# Client
##################################################

# Files
file (GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_executable (client ${CLIENT_SOURCE})
set_target_properties (client PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries (client core)

# Packaging
install (TARGETS client DESTINATION ${CMAKE_INSTALL_BINDIR})
install (FILES ${CLIENT_SOURCE} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PLATFORM}")
# Reinstall files from ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR} to the directory of the executable to avoid missing libraries errors.
file (GLOB_RECURSE CMAKE_INSTALL_BIN CONFIGURE_DEPENDS "${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/*")
file (INSTALL ${CMAKE_INSTALL_BIN} DESTINATION "${PROJECT_BINARY_DIR}/client")
