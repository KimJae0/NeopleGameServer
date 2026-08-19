#include "Server.h"
#include "Database.h"
#include <iostream>

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

    server.Run();

    return 0;


    /*
    Server server;

    if (server.Initialize() == false)
    {
        std::cout << "Server initialization failed!" << std::endl;
        return 1;
    }

    Player* player = server.FindPlayer(101);

    if (player == nullptr)
    {
        std::cout << "Player not found!" << std::endl;
        return 1;
    }

    player->SetStatus(900, 1000, 20, PlayerState::Alive);

    if (server.SavePlayer(101) == false)
    {
        std::cout << "Player save failed!" << std::endl;
        return 1;
    }

    std::cout << "Player saved!" << std::endl;

    return 0;
    */
    
    /*
    Server server;

    // Player 테스트
    server.AddPlayer(101);

    Player* player = server.FindPlayer(101);

    if(player != nullptr)
    {
        player->Move(100, 200);
        player->TakeDamage(70);

        PlayerStatus status = player->GetStatus();

        std::cout << "Player 101: "
                  << player->GetX() << " "
                  << player->GetY() << " "
                  << status.HP << " "
                  << to_string(status.State)
                  << std::endl;
    }

    server.Run();
    */

/*
    Database database;

    if (!database.Connect())
    {
        std::cout << "Database connection failed!" << std::endl;
        return 1;
    }
    Player player(101);

    if (database.LoadPlayer(101, player))
    {
        std::cout << "Player loaded!" << std::endl;

        PlayerStatus status = player.GetStatus();

        std::cout << "Player 101: "
                  << player.GetX() << " "
                  << player.GetY() << " "
                  << status.HP << " "
                  << to_string(status.State)
                  << std::endl;

        player.SetStatus(500, 700, 25, PlayerState::Alive);

        if (database.SavePlayer(player))
        {
            std::cout << "Player saved!" << std::endl;
        }
        else
        {
            std::cout << "Player save failed!" << std::endl;
        }
    }
    else
    {
        std::cout << "Player load failed!" << std::endl;
    }

    */
    return 0;
}