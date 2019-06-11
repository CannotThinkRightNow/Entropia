##################################################
# Compile Defintions
##################################################

message(STATUS ${SECTION_HEADER})
message(STATUS "Compile Defintions")
message(STATUS ${SECTION_SPLITTER})
# Boost
set(Boost_COMPILE_DEFINITIONS "BOOST_FILESYSTEM_NO_DEPRECATED")
add_compile_definitions(${Boost_COMPILE_DEFINITIONS})
list_to_string(Boost_COMPILE_DEFINITIONS " " Boost_COMPILE_DEFINITIONS_STRING)
message(STATUS "Boost: ${Boost_COMPILE_DEFINITIONS_STRING}")
# GLFW
set(GLFW_COMPILE_DEFINITIONS "GLFW_DLL")
add_compile_definitions(${GLFW_COMPILE_DEFINITIONS})
list_to_string(GLFW_COMPILE_DEFINITIONS " " GLFW_COMPILE_DEFINITIONS_STRING)
message(STATUS "GLFW: ${GLFW_COMPILE_DEFINITIONS_STRING}")
message(STATUS ${SECTION_FOOTER})
