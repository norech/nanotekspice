cmake_minimum_required(VERSION 3.15)

project(nano_tests)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC *.cpp) #*.cpp ../src/*.cpp ../src/components/*.cpp)

include_directories(
    "${CMAKE_CURRENT_SOURCE_DIR}/../src"
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME} ${SRC})

add_test(NAME ${PROJECT_NAME}_test
         COMMAND ${PROJECT_NAME}
         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
         )