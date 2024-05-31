cmake_minimum_required(VERSION 3.27)
project(graphs)

set(CMAKE_CXX_STANDARD 17)

add_executable(graphs main.cpp
        Graph.cpp myList.cpp
)

