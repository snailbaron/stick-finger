cmake_minimum_required(VERSION 4.0)

project(stick-finger)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(deps/SDL)

add_executable(stick-finger main.cpp)
target_link_libraries(stick-finger PRIVATE SDL3::SDL3)
