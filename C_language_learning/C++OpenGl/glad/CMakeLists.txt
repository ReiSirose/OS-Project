cmake_minimum_required(VERSION 3.10)

project(OpenGLTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

# 1. FIND PACKAGES (Cross-Platform)
# Use glfw3 for a robust configuration file search
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

# 3. EXECUTABLE
add_executable(opengl_test src/main.cpp src/glad.c src/Shader.cpp)

# 4. LINK LIBRARIES (Common)
# Link against the targets provided by find_package
target_link_libraries(opengl_test PRIVATE 
    glfw 
    OpenGL::GL
    glm::glm
)

# 5. HEADER SEARCH PATHS
# Ensure the GLAD headers are found
target_include_directories(opengl_test PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
)

# 6. PLATFORM-SPECIFIC CONFIGURATION

# Check if the current system is a Mac (APPLE is true on macOS)
if (APPLE)
    message(STATUS "Configuring for macOS (Apple)")
    
    target_link_libraries(opengl_test PRIVATE 
        "-framework Cocoa" 
        "-framework IOKit"
        "-framework CoreVideo"
    )

else()
    message(STATUS "Configuring for Linux or other OS")

endif()
