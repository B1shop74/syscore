
cmake_minimum_required(VERSION 3.20)

project(SysCore
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(syscore
    source/main.cpp
    source/systemInfo.cpp
    source/processInfo.cpp
)

target_compile_options(syscore PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

