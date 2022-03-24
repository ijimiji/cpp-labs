file(GLOB sources
     "src/*.hpp"
     "src/*.cpp"
)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix ${sources})
