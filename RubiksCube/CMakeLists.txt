cmake_minimum_required(VERSION 3.15)
project(RubiksCube)

set(CMAKE_CXX_STANDARD 17)

add_executable(RubiksCube RubiksCube/big_cube.h RubiksCube/cube_solution.cpp RubiksCube/cube_solution.h
        RubiksCube/)