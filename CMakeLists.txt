cmake_minimum_required(VERSION 3.23)
project(my_log_parser CXX)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(my_log_parser src/parser.cpp src/parser.h src/game.cpp src/game.h src/main.cpp src/report.cpp src/report.h )
