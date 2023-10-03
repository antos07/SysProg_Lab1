cmake_minimum_required(VERSION 3.26)
project(SysProg_Lab1 C)

set(CMAKE_C_STANDARD 17)

add_executable(SysProg_Lab1 main.c
        word_set.c
        word_set.h
        words.c
        words.h)
