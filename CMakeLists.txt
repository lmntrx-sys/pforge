cmake_minimum_required(VERSION 3.28)
project(pforge C)

set(CMAKE_C_STANDARD 17)

add_executable(pforge pforge.c
        tokens/Tokens.h
        tokens/TokenType.h
        tokens/Token.c
        common.h)
