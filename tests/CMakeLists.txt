project(tests)
add_subdirectory(lib)
add_executable(tests_run test.cpp)

target_link_libraries(tests_run pharma_lib)
target_link_libraries(tests_run gtest gtest_main)