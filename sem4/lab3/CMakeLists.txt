file(GLOB sources
     "src/win.cpp"
)

set(CMAKE_CXX_STANDARD 20)

add_executable(matrix WIN32 ${sources})
