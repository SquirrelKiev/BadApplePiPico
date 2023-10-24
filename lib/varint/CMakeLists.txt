cmake_minimum_required(VERSION 3.12)

project(varint)

add_library(varint INTERFACE)

target_sources(pico_st7789 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/varint.c
)

target_include_directories(pico_st7789 INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/
)