##################################################
# Utilities
##################################################

function (list_to_string list_var delimiter result_var)
  set(RESULT "" PARENT_SCOPE)
  foreach (item ${${list_var}})
    string(APPEND RESULT "${delimiter}${item}")
  endforeach (${item})
  string(LENGTH "${delimiter}" DELIMITER_LENGTH)
  string(SUBSTRING "${RESULT}" ${DELIMITER_LENGTH} -1 RESULT)
  set(${result_var} ${RESULT} PARENT_SCOPE)
endfunction ()

function (FetchContent_CheckAndPopulate name)
  FetchContent_GetProperties(${name})
  if (NOT ${name}_POPULATED)
    FetchContent_Populate(${name})
    add_subdirectory("${${name}_SOURCE_DIR}/${${name}_SOURCE_SUBDIR}" ${${name}_BINARY_DIR})
  endif ()
endfunction ()
