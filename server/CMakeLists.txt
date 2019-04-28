##################################################
# Server
##################################################

# Files
file(GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS "src/*")

# Targets
add_executable(server ${SERVER_SOURCE})
target_link_libraries(server core)

# Packaging
install(TARGETS server
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server")
