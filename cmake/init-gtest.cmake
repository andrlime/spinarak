find_package(GTest REQUIRED CONFIG)
file(GLOB_RECURSE TEST_OBJ_SOURCES "tests/*.cc")
add_executable(tests
	${TEST_OBJ_SOURCES}
)
target_link_libraries(tests
	GTest::gtest
	GTest::gtest_main
	SPINARAK_obj
)
include(GoogleTest)
gtest_discover_tests(tests)

target_include_directories(tests PRIVATE "./src/include")
