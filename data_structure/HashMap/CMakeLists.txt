cmake_minimum_required(VERSION 3.17)
project(HashMap C)

set(CMAKE_C_STANDARD 11)

add_executable(HashMap main.c HashMap.c HashMap.h Config.h)