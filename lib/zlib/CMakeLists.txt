cmake_minimum_required(VERSION 3.12)

project(zlib)

add_library(zlib INTERFACE)

target_sources(zlib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/adler32.c
    ${CMAKE_CURRENT_LIST_DIR}/src/compress.c
    ${CMAKE_CURRENT_LIST_DIR}/src/crc32.c
    ${CMAKE_CURRENT_LIST_DIR}/src/deflate.c
    ${CMAKE_CURRENT_LIST_DIR}/src/inffast.c
    ${CMAKE_CURRENT_LIST_DIR}/src/inflate.c
    ${CMAKE_CURRENT_LIST_DIR}/src/inftrees.c
    ${CMAKE_CURRENT_LIST_DIR}/src/trees.c
    ${CMAKE_CURRENT_LIST_DIR}/src/uncompr.c
    ${CMAKE_CURRENT_LIST_DIR}/src/zutil.c
)

target_include_directories(zlib INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/src/
)