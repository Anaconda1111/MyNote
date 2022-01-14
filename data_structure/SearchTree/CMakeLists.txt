cmake_minimum_required(VERSION 3.17)
project(SearchTree C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(SearchTree
        main.c
        main.h
        SearchTree.c
        SearchTree.h)
