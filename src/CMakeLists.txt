add_library(parserlib SHARED game.cpp myparser.cpp report.cpp)

target_include_directories(parserlib PUBLIC include)