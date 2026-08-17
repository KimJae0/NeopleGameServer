#pragma once

#include "Player.h"
#include "Session.h"
#include <unordered_map>
#include <winsock.h>

class Server{

    public:
        Server();
        void AddPlayer(int id);
        void RemovePlayer(int id);
        Player* FindPlayer(int id);
        int AddSession(SOCKET ClientSocket);
        Session* FindSession(int sessionId);
        void AcceptClient();

    private:
        std::unordered_map<int, Player> players;
        std::unordered_map<int, Session> sessions;
        int nextSessionId;
        SOCKET ListeningSocket;
        
};
