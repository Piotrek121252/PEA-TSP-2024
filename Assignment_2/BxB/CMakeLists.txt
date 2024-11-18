cmake_minimum_required(VERSION 3.27)
project(PEA_zadanie2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

add_executable(PEA_zadanie2 main.cpp
        TSPInstance.cpp
        TSPInstance.h
        GraphReader.cpp
        GraphReader.h
        TSP_BxB.cpp
        TSP_BxB.h
        TSP_BxB_new.cpp
        TSP_BxB_new.h)