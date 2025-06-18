cmake_minimum_required(VERSION 3.20)

project(
	SPINARAK
	VERSION 0.1
	DESCRIPTION "A GameBoy emulator written in modern C++"
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_FLAGS "-O0 -g")
set(CMAKE_CXX_FLAGS "-O3 -march=native -flto")

message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
message(STATUS "CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")


# -- Dependencies --

# -- Add files to object library --
file(GLOB_RECURSE SPINARAK_OBJ_SOURCES "src/*.cc")
list(FILTER SPINARAK_OBJ_SOURCES EXCLUDE REGEX ".*/main\\.cc$")
add_library(
	SPINARAK_obj OBJECT
	${SPINARAK_OBJ_SOURCES}
)
target_include_directories(SPINARAK_obj PRIVATE "./src/include")


# -- Link library and dependencies --
# none for now

# -- Create executable --
add_executable(SPINARAK_exe src/main.cc)
set_property(TARGET SPINARAK_exe PROPERTY OUTPUT_NAME SPINARAK)
target_include_directories(SPINARAK_exe PRIVATE "./src/include")
target_compile_features(SPINARAK_exe PRIVATE cxx_std_${CMAKE_CXX_STANDARD})

# -- Link object library and dependencies --
target_link_libraries(SPINARAK_exe PRIVATE SPINARAK_obj)

