cmake_minimum_required(VERSION 3.10)
project(parser-dev)

set(CMAKE_CXX_STANDARD 14)

add_executable(parse_test main.cpp src/simplemodel/SimpleModel.h src/simplemodel/SimpleIndex.h test/test_index.h src/parser/DoParse.h src/utils/utils.h src/parser/ParseSection.h src/mosdex/MosdexRoot.h src/parser/ParseDocument.h src/parser/ParseInfo.h src/parser/ParseData.h)

# sqlite3
target_link_libraries(parse_test sqlite3)

# spdlog
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../spdlog/include)

# RapidJSON
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../rapidjson/include)