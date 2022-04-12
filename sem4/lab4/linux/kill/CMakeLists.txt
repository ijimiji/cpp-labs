add_executable(kill main.cpp kill.cpp kill.hpp)
add_library(libkill 
STATIC 
kill.hpp
kill.cpp)