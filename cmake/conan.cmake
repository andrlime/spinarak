include("${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/generators/conan_toolchain.cmake")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE}/generators")
