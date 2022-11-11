cmake_minimum_required(VERSION 3.23)
project(my_log_parser C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(my_log_parser
        src/main.c
        src/report.c
        src/report.h
        src/parser.c
        src/parser.h)
