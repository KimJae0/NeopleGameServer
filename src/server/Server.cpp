#include "Server.h"


void Server::AddPlayer(int id)
{
    players.emplace(std::make_pair(id, Player(id)));

}

void Server::RemovePlayer(int id)
{
    players.erase(id);
}

Player* Server::FindPlayer(int id)
{
    auto it = players.find(id);

    if(it == players.end()){
        return nullptr;
    }
    
    return &it->second;
    
}

Server::Server(){
    nextSessionId = 1;
}

int Server::AddSession(){
    int curSessionId = nextSessionId;

    sessions[curSessionId] = Session();

    nextSessionId++;

    return curSessionId;
}

Session* Server::FindSession(int sessionId){
    auto it = sessions.find(sessionId);

    if(it == sessions.end()){
        return nullptr; 
    }

    return &it->second;
}