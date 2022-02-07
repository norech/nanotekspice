cmake_minimum_required(VERSION 3.20.5)

project(NanoTekSpice)

set(SRC
    src/main.cpp
)

include_directories(
    src/
)

add_executable(nanotekspice ${SRC})
