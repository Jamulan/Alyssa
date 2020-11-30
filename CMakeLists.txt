cmake_minimum_required(VERSION 3.17)
project(Alyssa)

set(CMAKE_PROJECT_VERSION_MAJOR  0)
set(CMAKE_PROJECT_VERSION_MINOR  1)
set(CMAKE_PROJECT_VERSION_PATCH  1)

include_directories(libs)

find_package(Vulkan REQUIRED FATAL_ERROR)
IF (WIN32)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(GLFW)
    add_subdirectory(glm)
ELSE()
    find_package(glfw3 REQUIRED)
ENDIF()

set(CMAKE_CXX_STANDARD 17)

add_executable(Alyssa src/Engine/Util.cpp src/Engine/Util.h src/Engine/Core.cpp src/Engine/Core.h src/Engine/Application.cpp src/Engine/Application.h src/Engine/Material.cpp src/Engine/Material.h src/Engine/Model.cpp src/Engine/Model.h src/Alyssa.cpp src/Game/Level.cpp src/Game/Level.h src/Game/Entity.cpp src/Game/Entity.h src/Game/PlayerCharacter.cpp src/Game/PlayerCharacter.h src/Game/Game.cpp src/Game/Game.h)
target_link_libraries(Alyssa glfw)
IF(WIN32)
    target_link_libraries(Alyssa glm)
    target_include_directories(Alyssa PUBLIC "C:/VulkanSDK/1.2.148.1/Lib")
    target_link_libraries(Alyssa Vulkan::Vulkan)
ELSE()
    target_link_libraries(Alyssa vulkan)
ENDIF()
add_custom_command(TARGET Alyssa PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:Alyssa>/assets)

