cmake_minimum_required(VERSION 3.8)
project(DungeonCrawl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp dungeon_crawl.cpp test.cpp test.cpp)
add_executable(DungeonCrawl ${SOURCE_FILES})