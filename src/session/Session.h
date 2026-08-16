#pragma once

class Session
{
public:
    Session();
    void ConnectPlayer(int id);
    int GetPlayerId();

private:
    int playerId;
};