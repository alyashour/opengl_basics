cmake_minimum_required(VERSION 3.31)
project(opengl_basics)

enable_language(C)

set(CMAKE_CXX_STANDARD 20)

# find packages
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# include dirs
include_directories(opengl_basics include)

# add executables
add_executable(opengl_basics
        src/main.cpp
        src/glad.c
        src/shader.h
)

# Make a custom target to copy over the shaders dir to the build dir
add_custom_target(copy_shaders ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders
        COMMENT "Copying shaders to build directory"
)

# Make your app depend on shaders being copied
add_dependencies(opengl_basics copy_shaders)

target_link_libraries(opengl_basics
        glfw
        ${OPENGL_LIBRARIES}
)
