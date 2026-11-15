cmake_minimum_required(VERSION 3.28)
project(pforge C)

set(CMAKE_C_STANDARD 17)

add_executable(pforge main.c
        Token.c
        ref_table.c
        lexer.c
        lexer.h
        ref_table.h
        Token.h
        common.h
        memory.h
        memory.c
        parser.h
        parser.c)
