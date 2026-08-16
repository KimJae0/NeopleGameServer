#pragma once

#include "Player.h"
#include "Session.h"
#include <unordered_map>

class Server{

    public:
        Server();
        void AddPlayer(int id);
        void RemovePlayer(int id);
        Player* FindPlayer(int id);
        int AddSession();
        Session* FindSession(int sessionId);

    private:
        std::unordered_map<int, Player> players;
        std::unordered_map<int, Session> sessions;
        int nextSessionId;
        
};
