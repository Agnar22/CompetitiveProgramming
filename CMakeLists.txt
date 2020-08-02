cmake_minimum_required(VERSION 3.10)
project(CompetitiveProgramming)

enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -pthread -lpthread -O3")

add_subdirectory(libs/googletest)
add_subdirectory(src/datastructures/trees)
add_subdirectory(tests)
