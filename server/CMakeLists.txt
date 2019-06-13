##################################################
# Server
##################################################

# Files
file(GLOB_RECURSE SERVER_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE SERVER_INCLUDE_PUBLIC CONFIGURE_DEPENDS "include/public/*")

# Targets
add_executable(server ${SERVER_SOURCE})
set_target_properties(server PROPERTIES PUBLIC_HEADER "${SERVER_INCLUDE_PUBLIC}"
                                        PRIVATE_HEADER "${PROJECT_GENERATED_INCLUDE_PRIVATE}")
target_include_directories(server PUBLIC "include/public"
                                  PRIVATE "${PROJECT_BINARY_DIR}/include/private")

# Libraries
# Core
target_link_libraries(server core)

# Packaging
install(TARGETS server
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server/public"
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server/private")
