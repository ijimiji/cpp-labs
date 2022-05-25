project(Lab)
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 20)

include_directories(App)
include_directories(Number)
include_directories(Vector)

add_subdirectory(App)
add_subdirectory(Number)
add_subdirectory(Vector)