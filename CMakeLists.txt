cmake_minimum_required(VERSION 3.28)
project(cstr C)

set(CMAKE_C_STANDARD 17)

set(BUILD_SHARED_LIBS off)

add_library(cstr cstr.c
        cstr.def.h cstr.h
        cstr.err.h
        cstr.cast.h
        cast.c
        cstr.strop.h
        strop.c)

add_executable(cstr_test test.c)

target_link_libraries(cstr_test cstr)

add_compile_definitions(__MACHINE_WORD_SIZE__=64)
#add_compile_definitions(__MACHINE_WORD_SIZE__=32)