cmake_minimum_required(VERSION 3.13)
project(parser-dev)

set(CMAKE_CXX_STANDARD 14)

add_executable(parse_test main.cpp src/SimpleModel.h src/SimpleIndex.h test/test_index.h src/DoParse.h src/utils.h)

# spdlog
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../spdlog/include)

# RapidJSON
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../rapidjson/include)