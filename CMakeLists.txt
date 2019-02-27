cmake_minimum_required(VERSION 3.13)
project(untitled)

set(CMAKE_CXX_STANDARD 14)

add_executable(parse_test main.cpp)


# RapidJSON
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../rapidjson/include)