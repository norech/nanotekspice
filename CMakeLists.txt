cmake_minimum_required(VERSION 3.15.0)

project(NanoTekSpice)

set(CMAKE_CXX_STANDARD 20)

set(SRC
    src/main.cpp
    src/components/ClockComponent.cpp
    src/components/InputComponent.cpp
    src/ComponentManager.cpp
)

include_directories(
    src/
)

add_executable(nanotekspice ${SRC})
