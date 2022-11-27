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
    ${RAINOUT_SOURCE_DIR}/openglRender.cpp
    ${RAINOUT_SOURCE_DIR}/utils.cpp
)

set(RAINOUT_ENGINE_SOURCES
    ${RAINOUT_SOURCE_DIR}/entity.cpp
    ${RAINOUT_SOURCE_DIR}/scene.cpp
)

add_subdirectory(${RAINOUT_3RDPARTY}/glfw)

add_library(rainout_render SHARED ${RAINOUT_CORE_SOURCES})
target_include_directories(rainout_render PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(rainout_render PRIVATE ${RAINOUT_INCLUDES})

add_library(rainout_engine SHARED ${RAINOUT_ENGINE_SOURCES})
target_include_directories(rainout_engine PRIVATE ${RAINOUT_INCLUDES})
target_include_directories(rainout_engine PRIVATE ${RAINOUT_CORE_INCLUDES})
target_link_libraries(rainout_engine rainout_render)

add_executable(Launcher ${CMAKE_SOURCE_DIR}/launcher/main.cpp ${RAINOUT_SOURCES})
target_include_directories(Launcher PRIVATE ${RAINOUT_CORE_INCLUDES})
target_include_directories(Launcher PRIVATE ${RAINOUT_INCLUDES})
target_link_libraries(Launcher glfw rainout_engine rainout_render)

add_executable(test_matrix ${CMAKE_SOURCE_DIR}/tests/matrix.cpp)
target_include_directories(test_matrix PRIVATE ${RAINOUT_INCLUDES})
