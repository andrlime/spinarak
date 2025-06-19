file(GLOB_RECURSE SPINARAK_OBJ_SOURCES "src/*.cc")
list(FILTER SPINARAK_OBJ_SOURCES EXCLUDE REGEX ".*/main\\.cc$")
add_library(
	SPINARAK_obj OBJECT
	${SPINARAK_OBJ_SOURCES}
)
target_include_directories(SPINARAK_obj PRIVATE "./src/include")

# -- Create executable --
add_executable(SPINARAK_exe src/main.cc)
set_property(TARGET SPINARAK_exe PROPERTY OUTPUT_NAME SPINARAK)
target_include_directories(SPINARAK_exe PRIVATE "./src/include")
target_compile_features(SPINARAK_exe PRIVATE cxx_std_${CMAKE_CXX_STANDARD})

# -- Link object library and dependencies --
target_link_libraries(SPINARAK_exe PRIVATE SPINARAK_obj)
