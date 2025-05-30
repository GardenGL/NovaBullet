cmake_minimum_required(VERSION 3.12)

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/null.cpp "")

project(STB)

add_library(STB STATIC include/STB/stb_image.h ${CMAKE_CURRENT_BINARY_DIR}/null.cpp)

target_include_directories(STB PUBLIC include)