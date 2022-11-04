cmake_minimum_required(VERSION 3.23)
find_package(MPI)

set(CXX_STANDARD 20)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})

add_executable(main main.cpp)

target_include_directories(main PUBLIC ${MPI_INCLUDE_PATH})
target_link_libraries(main ${MPI_CXX_LIBRARIES})
