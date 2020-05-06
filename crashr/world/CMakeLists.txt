file(GLOB_RECURSE _HDRS "*.h") 
file(GLOB_RECURSE _SRCS "*.cpp")
add_library(world ${_HDRS} ${_SRCS})
