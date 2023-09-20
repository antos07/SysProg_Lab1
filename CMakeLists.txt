cmake_minimum_required(VERSION 3.26)
project(SysProg_Lab1 C)

set(CMAKE_C_STANDARD 17)

add_executable(SysProg_Lab1 main.c
        word_map.c
        word_map.h
        words.c
        words.h)
