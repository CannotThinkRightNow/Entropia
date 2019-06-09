##################################################
# Server
##################################################

# Files
file(GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE SERVER_INCLUDE CONFIGURE_DEPENDS "include/*")

# Targets
add_executable(server ${SERVER_SOURCE})
set_target_properties(server PROPERTIES PUBLIC_HEADER "${SERVER_INCLUDE}")
target_include_directories(server PUBLIC "include")

# Libraries
# Core
target_link_libraries(server core)

# Packaging
install(TARGETS server
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server")
