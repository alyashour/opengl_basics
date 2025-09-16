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

# Copy shaders directory to the build directory after building
add_custom_command(
        TARGET opengl_basics POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders
        ${CMAKE_CURRENT_BINARY_DIR}/shaders
)

target_link_libraries(opengl_basics
        glfw
        ${OPENGL_LIBRARIES}
)
