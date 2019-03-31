cmake_minimum_required(VERSION 3.12)
project(PSU_myftp_2018 C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB_RECURSE sources src/*.c)
add_executable(myftp ${sources})

#file(GLOB_RECURSE tests_sources tests/src/*.c)
