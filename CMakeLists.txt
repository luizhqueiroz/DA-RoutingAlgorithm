cmake_minimum_required(VERSION 3.23)
project(code)

set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp code/Menu.cpp code/Menu.h code/Data.cpp code/Data.h code/Routing.cpp code/Routing.h code/data_structures/Graph.cpp code/data_structures/Graph.h code/data_structures/VertexEdge.cpp code/data_structures/VertexEdge.h)
