##################################################
# Utilities
##################################################

# Must be included before the first call to project().
# From: https://stackoverflow.com/a/48555098/9341868
function (get_arguments output_var log)
  get_cmake_property(ARGS CACHE_VARIABLES)
  foreach (ARG ${ARGS})
    get_property(ARG_HELP_STRING CACHE "${ARG}" PROPERTY HELPSTRING)
      if ("${ARG_HELP_STRING}" MATCHES "No help, variable specified on the command line." OR "${ARG_HELP_STRING}" STREQUAL "")
        if (log)
          message(STATUS "${ARG} = [${${ARG}}] - ${ARG_HELP_STRING}")
        endif ()
        list(APPEND ${output_var} "-D${ARG}=${${ARG}}")
      endif ()
  endforeach (${ARG})
  set(${output_var} ${${output_var}} PARENT_SCOPE)
endfunction ()

function (list_to_string list_var delimiter result_var)
  set(RESULT "" PARENT_SCOPE)
  foreach (item ${${list_var}})
    string(APPEND RESULT "${delimiter}${item}")
  endforeach (${item})
  string(LENGTH "${delimiter}" DELIMITER_LENGTH)
  string(SUBSTRING "${RESULT}" ${DELIMITER_LENGTH} -1 RESULT)
  set(${result_var} "${RESULT}" PARENT_SCOPE)
endfunction ()

function (Git_UpdateOrCheckSubmodules check)
  message(STATUS "${SECTION_HEADER}")
  message(STATUS "Submodules")
  file(STRINGS ".gitmodules" GIT_SUBMODULES_FILE)
  foreach (GIT_SUBMODULE_LINE ${GIT_SUBMODULES_FILE})
    string(FIND "${GIT_SUBMODULE_LINE}" "[" GIT_SUBMODULE_START)
    if (${GIT_SUBMODULE_START} EQUAL -1)
      set(GIT_SUBMODULE_START FALSE)
    else ()
      set(GIT_SUBMODULE_START TRUE)
    endif ()
    if (GIT_SUBMODULE_START)
      list(APPEND GIT_SUBMODULES ${GIT_SUBMODULE})
      set(GIT_SUBMODULE "${GIT_SUBMODULE_LINE}\n")
    else ()
      string(APPEND GIT_SUBMODULE "${GIT_SUBMODULE_LINE}\n")
    endif ()
  endforeach (${GIT_SUBMODULE_LINE})
  list(APPEND GIT_SUBMODULES "${GIT_SUBMODULE}")
  unset(GIT_SUBMODULE)
  foreach (GIT_SUBMODULE ${GIT_SUBMODULES})
    message(STATUS "${SECTION_SPLITTER}")
    # Name
    string(REGEX MATCH "\".+\"" GIT_SUBMODULE_NAME ${GIT_SUBMODULE})
    string(REPLACE "\"" "" GIT_SUBMODULE_NAME ${GIT_SUBMODULE_NAME})
    message(STATUS "Name: ${GIT_SUBMODULE_NAME}")
    # Path
    string(REGEX MATCH "path = .+" GIT_SUBMODULE_PATH ${GIT_SUBMODULE})
    string(REGEX REPLACE "path[ ]*=[ ]*" "" GIT_SUBMODULE_PATH ${GIT_SUBMODULE_PATH})
    string(REGEX REPLACE "\n.+" "" GIT_SUBMODULE_PATH ${GIT_SUBMODULE_PATH})
    set(GIT_SUBMODULE_PATH "${PROJECT_SOURCE_DIR}/${GIT_SUBMODULE_PATH}")
    message(STATUS "Path: ${GIT_SUBMODULE_PATH}")
    # Fetch
    execute_process(COMMAND git symbolic-ref refs/remotes/origin/HEAD WORKING_DIRECTORY ${GIT_SUBMODULE_PATH} OUTPUT_VARIABLE GIT_DEFAULT_BRANCH)
    string(REPLACE "refs/remotes/origin/" "" GIT_DEFAULT_BRANCH ${GIT_DEFAULT_BRANCH})
    string(REPLACE "\n" "" GIT_DEFAULT_BRANCH ${GIT_DEFAULT_BRANCH})
    execute_process(COMMAND git checkout ${GIT_DEFAULT_BRANCH} WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
    execute_process(COMMAND git fetch WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
    # Check
    if (check)
      message(STATUS "Checking '${GIT_SUBMODULE_NAME}'...")
      execute_process(COMMAND git status WORKING_DIRECTORY ${GIT_SUBMODULE_PATH} OUTPUT_VARIABLE GIT_STATUS_OUTPUT)
      string(FIND ${GIT_STATUS_OUTPUT} "up to date" GIT_SUBMODULE_UPDATED)
      string(FIND ${GIT_STATUS_OUTPUT} "Changes" GIT_SUBMODULE_MODIFIED)
      if (${GIT_SUBMODULE_UPDATED} EQUAL -1)
        message(FATAL_ERROR "Outdated '${GIT_SUBMODULE_NAME}' detected.")
      elseif (NOT ${GIT_SUBMODULE_MODIFIED} EQUAL -1)
        message(FATAL_ERROR "Modified '${GIT_SUBMODULE_NAME}' detected.")
      endif ()
      message(STATUS "Updated '${GIT_SUBMODULE_NAME}' detected.")
    # Update
    else ()
      message(STATUS "Updating '${GIT_SUBMODULE_NAME}'...")
      execute_process(COMMAND git reset --hard HEAD WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
      execute_process(COMMAND git pull WORKING_DIRECTORY ${GIT_SUBMODULE_PATH})
      execute_process(COMMAND git add ${GIT_SUBMODULE_NAME} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
      message(STATUS "Finished updating '${GIT_SUBMODULE_NAME}'.")
    endif ()
  endforeach (${GIT_SUBMODULE})
  message(STATUS "${SECTION_FOOTER}")
endfunction ()

function (FetchContent_CheckAndPopulate name args)
  FetchContent_GetProperties(${name})
  if (NOT ${name}_POPULATED)
    FetchContent_Populate(${name})
    add_subdirectory("${${name}_SOURCE_DIR}/${${name}_SOURCE_SUBDIR}" ${${name}_BINARY_DIR} ${args})
  endif ()
endfunction ()