#include "Server.h"
#include <iostream>


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
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if(result != 0){
        //생성 실패 처리
    }

    ListeningSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP
    );

    if (ListeningSocket == INVALID_SOCKET)
    {
        // 생성 실패 처리
    }

    sockaddr_in serverAddr = {};

    serverAddr.sin_family = AF_INET;

    serverAddr.sin_port = htons(9000);

    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result1 = bind(
        ListeningSocket,
        (sockaddr*)&serverAddr,
        sizeof(serverAddr)
    );

    if(result1 == SOCKET_ERROR)
    {
        // bind 실패
    }

    if (listen(ListeningSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        // 실패
    }
    else{
        std::cout << "Server Listening..." << std::endl;
    }

}

int Server::AddSession(SOCKET ClientSocket){
    int curSessionId = nextSessionId;

    sessions.emplace(std::make_pair(curSessionId, Session(ClientSocket)));
    
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


void Server::AcceptClient()
{
    SOCKET clientSocket = accept(
        ListeningSocket,
        nullptr,
        nullptr
    );

    if (clientSocket == INVALID_SOCKET)
    {
        return;
        // accept 실패
    }

    std::cout << "Client connected!" << std::endl;

    // 여기서 Session 생성
    int id = AddSession(clientSocket);

    Session* session = FindSession(id);

    if (session != nullptr)
    {
        std::string recvStr = session->Receive();

        std::cout << recvStr << std::endl;

        session->Send(recvStr);
    }
    std::cout << "Session ID: " << id << std::endl;
}