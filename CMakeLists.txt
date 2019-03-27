cmake_minimum_required(VERSION 3.13)
project(SimpleLex C)

set(CMAKE_C_STANDARD 99)

set(EXECUTABLE_OUTPUT_PATH ../build)

include_directories(include)
add_executable(SimpleLex main.c src/lexer.c src/lexer_value.c)