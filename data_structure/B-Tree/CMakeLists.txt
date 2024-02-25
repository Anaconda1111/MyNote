cmake_minimum_required(VERSION 3.17)
project(B_Tree C)

set(CMAKE_C_STANDARD 11)

add_executable(B_Tree main.c BTree.c BTree.h)