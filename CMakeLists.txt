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
)

target_link_libraries(opengl_basics
        glfw
        ${OPENGL_LIBRARIES}
)
