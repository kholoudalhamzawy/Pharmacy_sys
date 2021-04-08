cmake_minimum_required(VERSION 3.17)
project(pharmacy)

set(CMAKE_CXX_STANDARD 14)

add_executable(pharmacy_run main.cpp)
add_subdirectory(pharma)
include_directories(pharma)
target_link_libraries(pharmacy_run pharma_lib)

add_subdirectory(tests)