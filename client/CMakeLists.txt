##################################################
# Client
##################################################

# Files
file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CLIENT_INCLUDE_PUBLIC CONFIGURE_DEPENDS "include/public/*")

# Targets
add_executable(client ${CLIENT_SOURCE})
set_target_properties(client PROPERTIES OUTPUT_NAME "${PROJECT_NAME}"
                                        PUBLIC_HEADER "${CLIENT_INCLUDE_PUBLIC}"
                                        PRIVATE_HEADER "${PROJECT_GENERATED_INCLUDE_PRIVATE}")
target_include_directories(client PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/public>"
                                         "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/client/public>"
                                  PRIVATE "${PROJECT_BINARY_DIR}/include/private")

# Libraries
# Core
target_link_libraries(client PUBLIC core)

# Installation
install(TARGETS client
        EXPORT ${PROJECT_NAMESPACE}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/client/public"
        PRIVATE_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/client/private")

# Export
export(PACKAGE client)
