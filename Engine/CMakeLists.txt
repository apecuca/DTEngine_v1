cmake_minimum_required(VERSION 3.31.6)

# ---- config ----

project(Engine 
    LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED	ON)

# ---- sources ----

set(ENGINE_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/InputUtils.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/InternalSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PathSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/RenderingSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/SystemRegistry.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/TimeSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/WorldSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/InputSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PhysicsSystem.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PoolSystem.hpp
)

set(ENGINE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Component.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Entity.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/GameObject.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/TimeManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Utils.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/World.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/WorldManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/InputManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core/Transform.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/stb_image.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/RenderingManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Shader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Sprite.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/SpriteRenderer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Window.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/Animator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rendering/AnimationClip.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/Rigidbody.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/BoxCollider.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/physics/PhysicsManager.cpp
    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/SystemRegistry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PathSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/RenderingSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/TimeSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/WorldSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/InputSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PhysicsSystem.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/system/PoolSystem.cpp
)

# ---- library ----

add_library(Engine STATIC ${ENGINE_HEADERS} ${ENGINE_SOURCES})

# ---- find libraries ----

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(Stb REQUIRED)

# ---- directories ----

target_include_directories(Engine
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${Stb_INCLUDE_DIR}"
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/DTEngine"
)

# ---- linking ----

target_link_libraries(Engine
    PRIVATE
        glad::glad
        glfw
)

# ---- resources ----

set(RESOURCES_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/resources")
set(RESOURCES_DEST "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/resources")

add_custom_target(copy_resources ALL
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${RESOURCES_DEST}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${RESOURCES_SOURCE} ${RESOURCES_DEST}
    COMMENT "Refreshing resources folder"
)