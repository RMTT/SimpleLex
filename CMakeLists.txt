cmake_minimum_required(VERSION 3.13)
project(SimpleLex CXX)

set(CMAKE_CXX_STANDARD 11)

set(EXECUTABLE_OUTPUT_PATH ../build)

include_directories(include)
add_executable(SimpleLex main.cpp src/lexer.cpp src/lexer_value.cpp)