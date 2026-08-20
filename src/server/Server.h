#pragma once

#include "Player.h"
#include "Session.h"
#include "Database.h"
#include "TaskQueue.h"
#include <unordered_map>
#include <winsock.h>
#include <thread>
#include <vector>

class Server{

    public:
        Server();
        void AddPlayer(int id);
        void RemovePlayer(int id);
        Player* FindPlayer(int id);
        int AddSession(SOCKET ClientSocket);
        Session* FindSession(int sessionId);
        void AcceptClient();
        bool ProcessSession(Session* session);
        void Run();
        bool LoadPlayer(int id);
        bool Initialize();
        bool SavePlayer(int id);
        void Stop();

    private:
        std::unordered_map<int, Player> players;
        std::unordered_map<int, Session> sessions;
        int nextSessionId;
        SOCKET ListeningSocket;
        Database database;
        TaskQueue taskQueue;
        //std::thread workerThread;
        
        std::vector<std::thread> workerThreads;

        bool running;

        void WorkerFunction();

        
};
