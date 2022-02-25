add_library(Vector SHARED
    Vector.cpp
    Vector.hpp
)

target_link_directories(Vector PUBLIC Number)