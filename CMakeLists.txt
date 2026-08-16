cmake_minimum_required(VERSION 3.10)

project(NeopleGameServer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    ./src/main.cpp
    ./src/game/Player.cpp
    ./src/server/Server.cpp
    ./src/session/Session.cpp
)


add_executable(NeopleGameServer ${SOURCES})

target_include_directories(
    NeopleGameServer
    PRIVATE
    src/game
    src/server
    src/session
)
