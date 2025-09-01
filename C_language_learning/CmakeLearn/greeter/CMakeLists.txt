cmake_minimum_required(VERSION 3.16)

add_library(GreeterLib src/Greeter.cpp)
target_include_directories(GreeterLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)


target_compile_features(GreeterLib PUBLIC cxx_std_20)

set(LIBRARY_MESSAGE "This is the GreeterLib")
