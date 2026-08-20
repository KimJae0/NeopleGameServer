#include "Server.h"
#include "Database.h"
#include "taskqueue/TaskQueue.h"
#include <iostream>
#include <thread>

std::string to_string(PlayerState state)
{
    switch (state)
    {
    case PlayerState::Alive:
        return "Alive";
    case PlayerState::Dead:
        return "Dead";
    default:
        return "Unknown";
    }
}

int main()
{
    Server server;

    if (server.Initialize() == false)
    {
        std::cout << "Server initialization failed!" << std::endl;
        return 1;
    }

    std::thread inputThread([&server]()
    {
        std::cout << "Type exit to stop server." << std::endl;

        std::string command;

        while (std::cin >> command)
        {
            if (command == "exit")
            {
                server.Stop();
                break;
            }
        }
    });

    server.Run();

    inputThread.join();

    return 0;
}