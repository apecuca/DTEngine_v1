cmake_minimum_required(VERSION 3.10.0)

# Variables
set(EXECUTABLE_NAME DesktopGameEngine)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project
project(${EXECUTABLE_NAME} 
    LANGUAGES C CXX)

# Config lang
set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)
set(CMAKE_CXX_EXTENSIONS		OFF)

# Engine directory
add_subdirectory(Engine)

# Game directory
file(GLOB_RECURSE GAME_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Game/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game/*.hpp"
)

# 
add_executable(${EXECUTABLE_NAME} ${GAME_SOURCES})

# Include source dir to target
target_include_directories(Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link libraries
target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    Engine)