# This must be included AFTER conan
execute_process(
    COMMAND xcrun --sdk macosx --show-sdk-path
    OUTPUT_VARIABLE MACOSX_SYSROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
set(CMAKE_OSX_SYSROOT "${MACOSX_SYSROOT}" CACHE PATH "" FORCE)
