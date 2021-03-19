cmake_minimum_required(VERSION 3.16)
project(GraphLib VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(main main.cpp graph.h graph.cpp user_data.h)