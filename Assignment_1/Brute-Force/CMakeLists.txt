cmake_minimum_required(VERSION 3.27)
project(PEA_zadanie1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(PEA_zadanie1 main.cpp
        TSPInstance.cpp
        TSPInstance.h
        GraphReader.cpp
        GraphReader.h
        TSP_BF.cpp
        TSP_BF.h)