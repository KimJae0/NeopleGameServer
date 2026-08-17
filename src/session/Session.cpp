#include "Session.h"
#include "../server/Packet.h"
#include <vector>
#include <string>


Session::Session(SOCKET ClientSocket){
    playerId = 0;

    this->ClientSocket = ClientSocket;
}


void Session::ConnectPlayer(int id){
    playerId = id;
}


int Session::GetPlayerId(){
    return playerId;
}

int Session::Send(std::string data){
    return send(
        ClientSocket,
        data.c_str(),
        data.size(),
        0
    );
}


bool Session::Receive()
{
    std::vector<char> buffer(1024);

    int result = recv(
        ClientSocket,
        buffer.data(),
        buffer.size(),
        0
    );

    // 연결 종료 또는 오류
    if (result <= 0)
    {
        return false;
    }

    ReceiveBuffer.insert(
        ReceiveBuffer.end(),
        buffer.begin(),
        buffer.begin() + result
    );

    // Header조차 완성되지 않은 경우
    if (ReceiveBuffer.size() < sizeof(PacketHeader))
    {
        return false;
    }

    PacketHeader* header =
        reinterpret_cast<PacketHeader*>(ReceiveBuffer.data());

    // Packet 전체가 아직 도착하지 않은 경우
    if (ReceiveBuffer.size() < header->Size)
    {
        return false;
    }

    return true;
}


bool Session::PopPacket(std::vector<uint8_t>& packet)
{
    // Header가 충분히 있는지 확인
    if (ReceiveBuffer.size() < sizeof(PacketHeader))
    {
        return false;
    }

    // Header 얻기
    PacketHeader* header =
        reinterpret_cast<PacketHeader*>(ReceiveBuffer.data());

    // Packet Size 가져오기
    int packetSize = header->Size;

    // Packet 전체가 들어왔는지 확인
    if (ReceiveBuffer.size() < packetSize)
    {
        return false;
    }

    // packet에 Packet 복사
    packet.assign(
        ReceiveBuffer.begin(),
        ReceiveBuffer.begin() + packetSize
    );

    // ReceiveBuffer에서 Packet 제거
    ReceiveBuffer.erase(
        ReceiveBuffer.begin(),
        ReceiveBuffer.begin() + packetSize
    );

    return true;
}