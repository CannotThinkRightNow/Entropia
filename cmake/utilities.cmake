##################################################
# Utilities
##################################################

function (FetchContent_CheckAndPopulate name)
  FetchContent_GetProperties(${name})
  if (NOT ${name}_POPULATED)
    FetchContent_Populate(${name})
    add_subdirectory("${${name}_SOURCE_DIR}/${${name}_SOURCE_SUBDIR}" ${${name}_BINARY_DIR})
  endif ()
endfunction ()
