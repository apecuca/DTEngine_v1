cmake_minimum_required(VERSION 4.2.1)

project(Engine LANGUAGES C CXX)

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(Engine STATIC ${ENGINE_SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Engine PUBLIC
    glad::glad
    glfw
)