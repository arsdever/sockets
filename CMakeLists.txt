cmake_minimum_required(VERSION 3.10)

set(PROJECT sockets)
project(${PROJECT})

option(BUILD_SAMPLES "Build samples" ON)

add_subdirectory(src)

if(BUILD_SAMPLES)
  add_subdirectory(samples)
endif()
