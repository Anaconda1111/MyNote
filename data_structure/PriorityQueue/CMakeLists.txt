cmake_minimum_required(VERSION 3.17)
project(PriorityQueue C)

set(CMAKE_C_STANDARD 11)

add_executable(PriorityQueue main.c PriorityQueue.c PriorityQueue.h)