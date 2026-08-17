#pragma once
#include <winsock.h>
#include <string>
#include <vector>
#include <cstdint>

class Session
{
public:
    Session(SOCKET ClientSocket);
    void ConnectPlayer(int id);
    int GetPlayerId();
    int Send(std::string data);
    bool Receive();
    bool PopPacket(std::vector<uint8_t>& packet);

private:
    int playerId;
    SOCKET ClientSocket;
    std::vector<uint8_t> ReceiveBuffer;
};