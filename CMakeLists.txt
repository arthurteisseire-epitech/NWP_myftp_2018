cmake_minimum_required(VERSION 3.12)
project(PSU_myftp_2018 C)

add_compile_options(-Wall -Wextra)

include_directories(include)

file(GLOB_RECURSE sources src/*.c)
file(GLOB_RECURSE tests_sources tests/*.c)
add_executable(myftp ${sources} ${tests_sources})
target_link_libraries(myftp criterion)
