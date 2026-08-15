cmake_minimum_required(VERSION 3.10)

project(NeopleGameServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES ./src/main.cpp)

add_executable(NeopleGameServer ${SOURCES})