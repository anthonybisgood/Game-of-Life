cmake_minimum_required(VERSION 3.21)

project(GameOfLife22)

set(CMAKE_CXX_STANDARD 14)

# TODO: Change this to your path to catch.cpp
include_directories(/Users/abisg/CLionProjects)

add_executable(GameOfLife GameOfLife.cpp GameOfLifeTest.cpp)

# Use this to run the main method 
#add_executable(GameOfLife main.cpp)
