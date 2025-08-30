cmake_minimum_required(VERSION 3.16)
project(boyblue)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -Wextra -Wwrite-strings")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

set(SOURCES
    main.c
    src/cpu.c
    src/decoder.c
    src/mmu.c
    src/ppu.c
    src/log.c
)

add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)

add_executable(boyblue ${SOURCES})
target_link_libraries(boyblue PRIVATE SDL3::SDL3)
