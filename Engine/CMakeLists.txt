cmake_minimum_required(VERSION 3.31.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_include_directories(Engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/Engine"
)

target_link_libraries(Engine 
    PRIVATE
        glad::glad
        glfw
)