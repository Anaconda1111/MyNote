cmake_minimum_required(VERSION 3.17)
project(LeftistHeap C)

set(CMAKE_C_STANDARD 11)

add_executable(LeftistHeap main.c LeftistHeap.c LeftistHeap.h)