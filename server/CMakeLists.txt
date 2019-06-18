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
target_include_directories(server PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/public>"
                                         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/server/public>"
                                  PRIVATE "${PROJECT_BINARY_DIR}/include/private")

# Libraries
# Core
target_link_libraries(server PUBLIC core)

# Installation
install(TARGETS server
        EXPORT ${PROJECT_NAMESPACE}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server/public"
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/server/private")

# Export
export(PACKAGE server)
