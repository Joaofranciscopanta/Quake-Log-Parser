cmake_minimum_required(VERSION 3.23)
project(my_log_parser CXX)


set(CMAKE_C_STANDARD 17)

add_subdirectory(src)

enable_testing()

add_executable(my_log_parser src/myparser.cpp src/include/myparser.h src/game.cpp src/include/game.h src/main.cpp src/report.cpp src/include/report.h )
