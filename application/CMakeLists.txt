##################################################
# Application
##################################################
# Policies
cmake_minimum_required (VERSION 3.8)

# Files
configure_file ("src/config.h.in" "${CMAKE_CURRENT_LIST_DIR}/src/config.h")
file (GLOB_RECURSE APPLICATION_SOURCE "src/*")

# Target definitions
add_executable (${PROJECT_NAME} ${APPLICATION_SOURCE})

# Packaging
install (TARGETS ${PROJECT_NAME} DESTINATION bin)
install (FILES ${APPLICATION_SOURCE} DESTINATION include)
