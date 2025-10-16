cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})


find_package(OpenGL REQUIRED)

find_path(GLFW_INCLUDE_DIR NAMES GLFW/glfw3.h)

find_library(GLFW_LIBRARY NAMES glfw)

add_executable(opengl_test src/main.cpp src/glad.c src/shader.cpp)

# Add our 'include' and 'GLFW_INCLUDE_DIR' get from previous line
target_include_directories(opengl_test PRIVATE
    include
    ${GLFW_INCLUDE_DIR}
)

# Link the executable against the libraries it needs.
# 'glfw' and 'OpenGL::GL' are targets provided by find_package.
target_link_libraries(opengl_test PRIVATE glfw OpenGL::GL)
