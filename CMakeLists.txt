cmake_minimum_required(VERSION 3.14)

project(conway-game
    LANGUAGES CXX
    VERSION 1.0.0
)

add_executable(conway-game 
    src/grid.h
    src/grid.cpp
    src/main.cpp
    )
target_include_directories(conway-game PRIVATE src)

install(TARGETS conway-game RUNTIME DESTINATION "bin")
