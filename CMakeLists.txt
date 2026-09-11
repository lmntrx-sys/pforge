cmake_minimum_required(VERSION 3.28)
project(pforge C)

set(CMAKE_C_STANDARD 17)

add_executable(pforge pforge.c
        TokenType.h
        Token.c
        chunk.c
        lexer.c
        lexer.h
        chunk.h
        Token.h
        common.h
        memory.h
        memory.c)
