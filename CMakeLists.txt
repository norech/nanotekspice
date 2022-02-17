cmake_minimum_required(VERSION 3.15.0)

project(NanoTekSpice)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC
    main.cpp
    src/*.cpp
    src/**/*.cpp
)

include_directories(
    src/
)

add_executable(nanotekspice ${SRC})
