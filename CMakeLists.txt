cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(randomsim)

include(cmake/dependencies.cmake)
include(cmake/flags.cmake)

include_directories(inc)
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

