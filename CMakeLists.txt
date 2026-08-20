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
    ./src/database/Database.cpp
    ./src/taskqueue/TaskQueue.cpp
)

set(SOURCES1
    ./src/client/client.cpp
)

set(TASK_QUEUE_TEST
    ./src/test/TaskQueueTest.cpp
    ./src/taskqueue/TaskQueue.cpp
)

add_executable(NeopleGameServer ${SOURCES})
add_executable(NeopleGameClient ${SOURCES1})

add_executable(TaskQueueTest ${TASK_QUEUE_TEST})

target_include_directories(
    NeopleGameServer
    PRIVATE
    src/game
    src/server
    src/session
    src/database
    src/taskqueue
)

target_include_directories(
    TaskQueueTest
    PRIVATE
    src/taskqueue
    src/game
)


target_link_libraries(NeopleGameServer PRIVATE ws2_32)
target_link_libraries(NeopleGameClient PRIVATE ws2_32)

# MySQL Connector/C++
set(mysql-concpp_DIR "C:/Users/tkrhk/Downloads/mysql-connector-c++-26.7.0-winx64/mysql-connector-c++-26.7.0-winx64")

find_package(mysql-concpp REQUIRED)

target_link_libraries(NeopleGameServer PRIVATE mysql::concpp)