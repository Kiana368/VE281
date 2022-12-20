cmake_minimum_required(VERSION 3.16)
project(proj1)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj1 main.cpp)
add_executable(gsa p1.cpp)
add_executable(test p1test.cpp)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -pedantic -Wno-unused-result")