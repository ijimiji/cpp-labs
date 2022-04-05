file(GLOB sources
     "src/posix.cpp"
)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix ${sources})
