##################################################
# Compile Defintions
##################################################

message(STATUS "${SECTION_HEADER}")
message(STATUS "Compile Defintions")
message(STATUS "${SECTION_SPLITTER}")
# Boost
set(Boost_COMPILE_DEFINITIONS "BOOST_FILESYSTEM_NO_DEPRECATED")
add_compile_definitions(${Boost_COMPILE_DEFINITIONS})
list_to_string(Boost_COMPILE_DEFINITIONS " " Boost_COMPILE_DEFINITIONS_STRING)
message(STATUS "Boost: ${Boost_COMPILE_DEFINITIONS_STRING}")
message(STATUS "${SECTION_FOOTER}")
