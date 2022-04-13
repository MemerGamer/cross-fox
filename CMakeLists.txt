cmake_minimum_required(VERSION 3.20)
project(cross_fox C)

set(CMAKE_C_STANDARD 99)

add_executable(cross_fox fox/src/main.c fox/src/utils.c fox/headers/utils.h)
