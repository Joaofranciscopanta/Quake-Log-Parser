cmake_minimum_required(VERSION 3.23)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e # release-1.10.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(parse_test src/parser_test.cpp
        src/myparser.cpp
        src/game.cpp
        src/include/game.h
        src/report.cpp
        src/include/report.h)
target_link_libraries(parse_test PRIVATE GTest::GTest)