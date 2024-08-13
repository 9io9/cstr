cmake_minimum_required(VERSION 3.28)
project(cstr C)

set(CMAKE_C_STANDARD 17)

set(BUILD_SHARED_LIBS off)

add_library(cstr cstr.c
        cstr.def.h cstr.h
        cstr.err.h)