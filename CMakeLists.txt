cmake_minimum_required(VERSION 3.20)
project(drone)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_compile_options(-std=c++17 -g -Wall -Wextra -pedantic)

add_library(udp udpsocket.cpp)

add_executable(repl repl.cpp)
target_link_libraries(repl PUBLIC udp)

add_executable(state state.cpp)
target_link_libraries(state PUBLIC udp)

find_package(OpenCV REQUIRED)
add_executable(video video.cpp)
target_include_directories(video PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(video PUBLIC udp ${OpenCV_LIBS})
