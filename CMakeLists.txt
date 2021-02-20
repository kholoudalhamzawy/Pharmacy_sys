cmake_minimum_required(VERSION 3.17)
project(pharmacy)

set(CMAKE_CXX_STANDARD 14)

add_executable(pharmacy main.cpp pharmacy.cpp cmake-build-debug/pharmacy.h pharmacy.h)