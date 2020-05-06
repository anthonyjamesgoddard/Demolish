file(GLOB_RECURSE _HDRS "*.h") 
file(GLOB_RECURSE _SRCS "*.cpp")
add_library(lib2 ${_HDRS} ${_SRCS})
