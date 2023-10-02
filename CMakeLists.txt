cmake_minimum_required(VERSION 3.10)
project(RG_Pairing)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(RG_Pairing 
    src/main.cpp 
    src/coarse_grain.cpp
    src/pairwise_evidence.cpp
    src/helper_functions.cpp
    src/file_io.cpp
    src/sample_binary_vars.cpp
    src/timer.cpp
)

