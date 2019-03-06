cmake_minimum_required(VERSION 3.13)
project(parser-dev)

set(CMAKE_CXX_STANDARD 14)

add_executable(parse_test main.cpp src/simplemodel/SimpleModel.h src/simplemodel/SimpleIndex.h test/test_index.h src/parser/DoParse.h src/utils/utils.h src/parser/ParseFactory.h)

# spdlog
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../spdlog/include)

# RapidJSON
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../rapidjson/include)