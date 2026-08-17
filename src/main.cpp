#include "Server.h"
#include <iostream>

std::string to_string(PlayerState state) {
    switch (state) {
        case PlayerState::Alive: return "Alive";
        case PlayerState::Dead: return "Dead";
        default: return "Unknown";
    }
}

int main()
{
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

    server.AcceptClient();

    return 0;
}