cmake_minimum_required(VERSION 3.31.7)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Internal LANGUAGES C CXX)

file(GLOB_RECURSE INTERNAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(Internal STATIC ${INTERNAL_SOURCES})

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)

target_include_directories(Internal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(Internal PUBLIC
    glad::glad
    glfw
)