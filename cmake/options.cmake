##################################################
# Options
##################################################

# Provide

# Set
# Common
set(BUILD_SHARED_LIBS ON CACHE BOOL "Global flag to cause add_library() to create shared libraries if on." FORCE)

# GLEW
set(BUILD_UTILS ON CACHE BOOL "utilities" FORCE)
set(GLEW_REGAL OFF CACHE BOOL "Regal mode" FORCE)
set(GLEW_OSMESA OFF CACHE BOOL "OSMesa mode" FORCE)

# GLFW
# set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
set(GLFW_INSTALL ON CACHE BOOL "Generate installation target" FORCE)
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "Assume the Vulkan loader is linked with the application" FORCE)

# spdlog
set(SPDLOG_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)
set(SPDLOG_BUILD_BENCH OFF CACHE BOOL "Build benchmarks (Requires https://github.com/google/benchmark.git to be installed)" FORCE)
set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "Build tests" FORCE)
set(SPDLOG_BUILD_HO_TESTS OFF CACHE BOOL "Build tests using the header only version" FORCE)
set(SPDLOG_SANITIZE_ADDRESS OFF CACHE BOOL "Enable address sanitizer in tests" FORCE)
set(SPDLOG_INSTALL ON CACHE BOOL "Generate the install target." FORCE)
set(SPDLOG_FMT_EXTERNAL OFF CACHE BOOL "Use external fmt library instead of bundled" FORCE)

# GLM
set(GLM_QUIET OFF CACHE BOOL "No CMake Message" FORCE)
# set(BUILD_SHARED_LIBS ON CACHE BOOL "Build shared library" FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL "Build static library" FORCE)
set(GLM_TEST_ENABLE_CXX_98 OFF CACHE BOOL "Enable C++ 98" FORCE)
set(GLM_TEST_ENABLE_CXX_11 OFF CACHE BOOL "Enable C++ 11" FORCE)
set(GLM_TEST_ENABLE_CXX_14 OFF CACHE BOOL "Enable C++ 14" FORCE)
set(GLM_TEST_ENABLE_CXX_17 OFF CACHE BOOL "Enable C++ 17" FORCE)
set(GLM_TEST_ENABLE_CXX_20 OFF CACHE BOOL "Enable C++ 20" FORCE)
set(GLM_TEST_ENABLE_LANG_EXTENSIONS OFF CACHE BOOL "Enable language extensions" FORCE)
set(GLM_DISABLE_AUTO_DETECTION OFF CACHE BOOL "Enable language extensions" FORCE)
set(GLM_TEST_ENABLE_FAST_MATH OFF CACHE BOOL "Enable fast math optimizations" FORCE)
set(GLM_TEST_ENABLE OFF CACHE BOOL "Build unit tests" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE2 OFF CACHE BOOL "Enable SSE2 optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE3 OFF CACHE BOOL "Enable SSE3 optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSSE3 OFF CACHE BOOL "Enable SSSE3 optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE4_1 OFF CACHE BOOL "Enable SSE 4.1 optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_SSE4_2 OFF CACHE BOOL "Enable SSE 4.2 optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX OFF CACHE BOOL "Enable AVX optimizations" FORCE)
set(GLM_TEST_ENABLE_SIMD_AVX2 OFF CACHE BOOL "Enable AVX2 optimizations" FORCE)
set(GLM_TEST_FORCE_PURE OFF CACHE BOOL "Force 'pure' instructions" FORCE)
