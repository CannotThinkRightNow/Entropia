##################################################
# Patches
##################################################

# GLEW
macro (fix_glew_include_directory target)
  FetchContent_GetProperties(glew_project)
  target_include_directories(${target} PUBLIC "$<BUILD_INTERFACE:${glew_project_SOURCE_DIR}/include>")
endmacro ()

# GLFW
macro (fix_glfw_include_directory target)
  FetchContent_GetProperties(glfw_project)
  target_include_directories(${target} PUBLIC "$<BUILD_INTERFACE:${glfw_project_SOURCE_DIR}/include>")
endmacro ()
