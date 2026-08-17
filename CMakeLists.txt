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

set(SOURCES1
    ./src/client/client.cpp
)

add_executable(NeopleGameServer ${SOURCES})

add_executable(NeopleGameClient ${SOURCES1})

target_include_directories(
    NeopleGameServer
    PRIVATE
    src/game
    src/server
    src/session
)


target_link_libraries(NeopleGameServer PRIVATE ws2_32)
target_link_libraries(NeopleGameClient PRIVATE ws2_32)