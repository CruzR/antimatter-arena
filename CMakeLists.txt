cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

include_directories(src)

add_subdirectory(src)
add_subdirectory(unittests)
