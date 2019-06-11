##################################################
# Client
##################################################

# Files
file(GLOB_RECURSE CLIENT_SOURCE CONFIGURE_DEPENDS "src/*")
file(GLOB_RECURSE CLIENT_INCLUDE CONFIGURE_DEPENDS "include/*")

# Targets
add_executable(client ${CLIENT_SOURCE})
set_target_properties(client PROPERTIES PUBLIC_HEADER "${CLIENT_INCLUDE}")
set_target_properties(client PROPERTIES OUTPUT_NAME "${PROJECT_NAME}")
target_include_directories(client PUBLIC "include")

# Libraries
# Core
target_link_libraries(client core)

# Packaging
install(TARGETS client
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/client")
