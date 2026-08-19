#include "Server.h"
#include <iostream>
#include "Packet.h"

void Server::AddPlayer(int id)
{
    players.emplace(std::make_pair(id, Player(id)));
}

void Server::RemovePlayer(int id)
{
    players.erase(id);
}

Player *Server::FindPlayer(int id)
{
    auto it = players.find(id);

    if (it == players.end())
    {
        return nullptr;
    }

    return &it->second;
}

Server::Server()
{
    nextSessionId = 1;
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        // 생성 실패 처리
    }

    ListeningSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

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
        (sockaddr *)&serverAddr,
        sizeof(serverAddr));

    if (result1 == SOCKET_ERROR)
    {
        // bind 실패
    }

    if (listen(ListeningSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        // 실패
    }
    else
    {
        std::cout << "Server Listening..." << std::endl;
    }
}

int Server::AddSession(SOCKET ClientSocket)
{
    int curSessionId = nextSessionId;

    sessions.emplace(std::make_pair(curSessionId, Session(ClientSocket)));

    nextSessionId++;

    return curSessionId;
}

Session *Server::FindSession(int sessionId)
{
    auto it = sessions.find(sessionId);

    if (it == sessions.end())
    {
        return nullptr;
    }

    return &it->second;
}

void Server::AcceptClient()
{
    SOCKET clientSocket = accept(
        ListeningSocket,
        nullptr,
        nullptr);

    if (clientSocket == INVALID_SOCKET)
    {
        return;
        // accept 실패
    }

    std::cout << "Client connected!" << std::endl;

    // 여기서 Session 생성
    int id = AddSession(clientSocket);

    Session *session = FindSession(id);

    if (session != nullptr)
    {
        session->ConnectPlayer(101);
    }
    std::cout << "Session ID: " << id << std::endl;
}

bool Server::ProcessSession(Session *session)
{
    // 여기에서 Session의 데이터를 계속 처리
    bool result = session->Receive();

    if (result)
    {
        std::vector<uint8_t> packet;

        while (session->PopPacket(packet))
        {
            PacketHeader *header =
                reinterpret_cast<PacketHeader *>(packet.data());

            if (header->Type == PacketType::Move)
            {
                // MovePacket으로 변환
                MovePacket *movePacket =
                    reinterpret_cast<MovePacket *>(packet.data());

                int playerId = session->GetPlayerId();

                Player *player = FindPlayer(playerId);

                if (player != nullptr)
                {
                    player->Move(
                        movePacket->X,
                        movePacket->Y);

                    std::cout << "Packet: X=" << movePacket->X
                              << " Y=" << movePacket->Y << std::endl;

                    std::cout << "Player: X=" << player->GetX()
                              << " Y=" << player->GetY() << std::endl;
                }
            }
        }

        return true;
    }

    return false;
}

void Server::Run()
{
    while (true)
    {
        fd_set readSet;

        FD_ZERO(&readSet);

        FD_SET(ListeningSocket, &readSet);

        for (auto &pair : sessions)
        {
            FD_SET(pair.second.GetSocket(), &readSet);
        }

        int result = select(
            0,
            &readSet,
            nullptr,
            nullptr,
            nullptr);

        if (result == SOCKET_ERROR)
        {
            // 오류 처리
            continue;
        }

        if (FD_ISSET(ListeningSocket, &readSet))
        {
            AcceptClient();
        }

        std::vector<int> disconnectedSessions;

        for (auto &pair : sessions)
        {
            // 현재 Session의 Socket이 준비되었는지 확인

            if (FD_ISSET(pair.second.GetSocket(), &readSet))
            {
                Session *session = &pair.second;

                if (ProcessSession(session) == false)
                {
                    disconnectedSessions.push_back(pair.first);
                }
            }

            // 준비되었다면 ProcessSession() 호출
        }

        for (int sessionId : disconnectedSessions)
        {
            Session *session = FindSession(sessionId);

            if (session != nullptr)
            {
                session->Close();
                sessions.erase(sessionId);
            }
            // sessions에서 sessionId 제거
        }
    }
}

bool Server::LoadPlayer(int id)
{

    AddPlayer(id);

    Player *player = FindPlayer(id);

    if (player != nullptr)
    {
        if (database.LoadPlayer(id, *player))
        {
            std::cout << "Player loaded: " << id << std::endl;
            return true;
        }
        else
        {
            RemovePlayer(id);
            return false;
        }
    }
    else{
        return false;
    }
}


bool Server::Initialize(){
    
    
    if(database.Connect() == false){
        return false;
    }
    std::cout << "Database connected!" << std::endl;

    if(LoadPlayer(101) == false){
        return false;
    }

    return true;
}

bool Server::SavePlayer(int id){
    Player* player = FindPlayer(id);

    if (player == nullptr)
    {
        return false;
    }

    return database.SavePlayer(*player);
}