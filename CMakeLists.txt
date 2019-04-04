cmake_minimum_required(VERSION 3.12)
project(PSU_myftp_2018 C)

add_compile_options(-Wall -Wextra)

include_directories(include lib/string_ext/include)

file(GLOB_RECURSE sources src/*.c)
file(GLOB_RECURSE lib lib/string_ext/*.c)
add_executable(myftp ${sources} ${lib})
target_link_libraries(myftp)
