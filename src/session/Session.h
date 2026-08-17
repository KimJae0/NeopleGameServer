#pragma once
#include <winsock.h>
#include <string>

class Session
{
public:
    Session(SOCKET ClientSocket);
    void ConnectPlayer(int id);
    int GetPlayerId();
    int Send(std::string data);
    std::string Receive();

private:
    int playerId;
    SOCKET ClientSocket;
};