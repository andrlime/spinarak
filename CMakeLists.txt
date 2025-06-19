cmake_minimum_required(VERSION 3.20)

project(
	SPINARAK
	VERSION 0.1
	DESCRIPTION "A GameBoy emulator written in modern C++"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 26)

include("cmake/build-type.cmake")
include("cmake/conan.cmake")

if(APPLE)
    include("cmake/macos-hotfix.cmake")
endif()

include("cmake/init-gtest.cmake")
include("cmake/init-spinarak.cmake")
