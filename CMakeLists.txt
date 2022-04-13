cmake_minimum_required(VERSION 3.20)
project(cross_fox C)

set(CMAKE_C_STANDARD 99)

add_executable(cross_fox main.c cmake-build-debug/DataStructures/Lists/Node.c cmake-build-debug/DataStructures/Lists/Node.h)
