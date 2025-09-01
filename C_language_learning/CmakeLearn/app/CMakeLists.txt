cmake_minimum_required(VERSION 3.16)

set(SRC_DIR "src")
set(MAIN_FILE "main.cpp")

add_executable(GreeterApp "${SRC_DIR}/${MAIN_FILE}")
target_compile_features(GreeterApp PUBLIC cxx_std_20)

target_link_libraries(GreeterApp GreeterLib)
target_include_directories(GreeterApp PUBLIC 
  ${PROJECT_SOURCE_DIR}/greeter/include/greeter 
)