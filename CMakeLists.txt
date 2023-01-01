cmake_minimum_required(VERSION 3.0.1 FATAL_ERROR)
project(Rainout)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
    add_compile_definitions(-DRAINOUT_PLATFORM_WINDOWS)
endif()

set(RAINOUT_INCLUDES ${CMAKE_SOURCE_DIR}/include/)
set(RAINOUT_3RDPARTY ${CMAKE_SOURCE_DIR}/3rdparty)

set(RAINOUT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(RAINOUT_DEBUG_DIR ${CMAKE_SOURCE_DIR}/build/debug)
set(RAINOUT_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

if(MSVC)
    add_compile_definitions(-DRAINOUT_PLATFORM_WINDOWS)
endif()

set(RAINOUT_CORE_INCLUDES
    ${RAINOUT_3RDPARTY}/glad/include/
    ${RAINOUT_3RDPARTY}/glfw/include/
    ${CMAKE_SOURCE_DIR}/core/
)

set(RAINOUT_CORE_SOURCES
    ${RAINOUT_3RDPARTY}/glad/src/glad.c
    ${RAINOUT_SOURCE_DIR}/openglRender.cpp
    ${RAINOUT_SOURCE_DIR}/windowManager.cpp
    ${RAINOUT_SOURCE_DIR}/texture.cpp
    ${RAINOUT_SOURCE_DIR}/utils.cpp
)

set(RAINOUT_ENGINE_SOURCES
    ${RAINOUT_SOURCE_DIR}/utils.cpp
    ${RAINOUT_SOURCE_DIR}/scene.cpp
    ${RAINOUT_SOURCE_DIR}/entity.cpp
    ${RAINOUT_SOURCE_DIR}/texture.cpp
    ${RAINOUT_SOURCE_DIR}/keyboard.cpp
    ${RAINOUT_SOURCE_DIR}/assetManager.cpp
)

add_subdirectory(${RAINOUT_3RDPARTY}/glfw)

# Raintout code libraries
#TODO: This shouldn't be called 'rainout_render' anymore
add_library(rainout_render SHARED ${RAINOUT_CORE_SOURCES})
target_include_directories(rainout_render PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(rainout_render PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(rainout_render glfw)
target_compile_definitions(rainout_render PRIVATE -DRAINOUT_PLATFORM_WINDOWS)
target_compile_definitions(rainout_render PRIVATE -DRAINOUT_IMPLEMENTATION)

# Rainout engine libraries
add_library(rainout_engine SHARED ${RAINOUT_ENGINE_SOURCES})
target_include_directories(rainout_engine PRIVATE ${RAINOUT_INCLUDES})
target_include_directories(rainout_engine PRIVATE ${RAINOUT_CORE_INCLUDES})
target_link_libraries(rainout_engine rainout_render)
target_compile_definitions(rainout_engine PRIVATE -DRAINOUT_PLATFORM_WINDOWS)
target_compile_definitions(rainout_engine PRIVATE -DRAINOUT_IMPLEMENTATION)

# Rainout launcher
add_executable(Launcher ${CMAKE_SOURCE_DIR}/launcher/main.cpp ${RAINOUT_SOURCES})
target_include_directories(Launcher PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(Launcher PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(Launcher rainout_engine rainout_render)
target_compile_definitions(Launcher PRIVATE -DRAINOUT_PLATFORM_WINDOWS)
target_compile_definitions(Launcher PRIVATE -DRAINOUT_IMPLEMENTATION)

add_custom_command(
    TARGET Launcher 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${RAINOUT_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_DEBUG_DIR}/Launcher.exe ${RAINOUT_BINARY_DIR}/Launcher.exe
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_DEBUG_DIR}/rainout_engine.dll ${RAINOUT_BINARY_DIR}/rainout_engine.dll
    COMMAND ${CMAKE_COMMAND} -E copy ${RAINOUT_DEBUG_DIR}/rainout_render.dll ${RAINOUT_BINARY_DIR}/rainout_render.dll
)

add_subdirectory(${CMAKE_SOURCE_DIR}/demos/pong/)
add_subdirectory(${CMAKE_SOURCE_DIR}/demos/controller/)
add_subdirectory(${CMAKE_SOURCE_DIR}/demos/SpaceShooter/)
