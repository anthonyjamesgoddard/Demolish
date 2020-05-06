cmake_minimum_required(VERSION 3.10)

project(crashr)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include_directories(crashr)

# include testing framework here

add_subdirectory(docs)
add_subdirectory(crashr)
