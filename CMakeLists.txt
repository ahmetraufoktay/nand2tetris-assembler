cmake_minimum_required(VERSION 3.16)

project(assembler
    VERSION 1.0
    LANGUAGES C
)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES src/*.c)

add_executable(assembler
    ${SRC_FILES}
)
target_include_directories(assembler
    PRIVATE include
)
