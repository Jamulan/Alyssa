cmake_minimum_required(VERSION 3.17)
project(Alyssa)

include_directories(libs)

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Alyssa main.cpp)
target_link_libraries(Alyssa glfw)
target_link_libraries(Alyssa vulkan)
target_link_libraries(Alyssa glslang)
target_link_libraries(Alyssa SPIRV)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})