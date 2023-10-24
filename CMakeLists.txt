cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(bad_apple)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project

add_subdirectory("lib/st7789")
add_subdirectory("lib/varint")
add_subdirectory("lib/zlib")

add_executable(bad_apple
    main.c
    chain_decode.c
)

target_link_libraries(bad_apple pico_stdlib hardware_spi pico_st7789 zlib)

pico_add_extra_outputs(bad_apple)