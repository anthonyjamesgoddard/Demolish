file(GLOB_RECURSE _HDRS "*.h") 
file(GLOB_RECURSE _SRCS "*.cpp")
add_library(geo ${_HDRS} ${_SRCS})
