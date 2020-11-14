cmake_minimum_required(VERSION 3.17)
project(Alyssa)

set(CMAKE_PROJECT_VERSION_MAJOR  0)
set(CMAKE_PROJECT_VERSION_MINOR  1)
set(CMAKE_PROJECT_VERSION_PATCH  1)

include_directories(libs)

find_package(Vulkan REQUIRED FATAL_ERROR)
find_package(glfw3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(Vulkan-First src/main.cpp src/main.h)
target_link_libraries(Vulkan-First glfw)
target_link_libraries(Vulkan-First vulkan)

add_executable(Alyssa src/Engine/Util.cpp src/Engine/Util.h src/Engine/Core.cpp src/Engine/Core.h src/Engine/Application.cpp src/Engine/Application.h src/Engine/Material.cpp src/Engine/Material.h src/Engine/Model.cpp src/Engine/Model.h src/Engine/World.cpp src/Engine/World.h src/Alyssa.cpp)
target_link_libraries(Alyssa glfw)
target_link_libraries(Alyssa vulkan)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
