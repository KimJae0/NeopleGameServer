#include <iostream>
#include <winsock.h>
#include <vector>
#include <string>
#include <iostream>

#include "../server/Packet.h"

int main()
{
    // 1. Winsock 초기화
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        std::cout << "WSAStartup failed" << std::endl;
        return 1;
    }

    // 2. Client Socket 생성
    SOCKET clientSocket = socket(
        AF_INET,
        SOCK_STREAM,
        IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET)
    {
        std::cout << "Socket creation failed" << std::endl;
        WSACleanup();
        return 1;
    }

    // 3. 연결할 Server 주소 설정
    sockaddr_in serverAddr = {};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(9000);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 4. Server에 연결
    result = connect(
        clientSocket,
        (sockaddr *)&serverAddr,
        sizeof(serverAddr));

    if (result == SOCKET_ERROR)
    {
        std::cout << "Connect failed" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to Server!" << std::endl;

    MovePacket packet1;
    packet1.X = 150;
    packet1.Y = 300;
    packet1.Header.Size = sizeof(packet1);
    packet1.Header.Type = PacketType::Move;

    MovePacket packet2;
    packet2.X = 500;
    packet2.Y = 700;
    packet2.Header.Size = sizeof(packet2);
    packet2.Header.Type = PacketType::Move;

    MovePacket packet3;
    packet3.X = 650;
    packet3.Y = 950;
    packet3.Header.Size = sizeof(packet3);
    packet3.Header.Type = PacketType::Move;

    int sendResult1 = send(
        clientSocket,
        reinterpret_cast<const char *>(&packet1),
        sizeof(packet1),
        0);

    std::cout << "send 1: " << sendResult1 << std::endl;

    int sendResult2 = send(
        clientSocket,
        reinterpret_cast<const char *>(&packet2),
        sizeof(packet2),
        0);

    std::cout << "send 2: " << sendResult2 << std::endl;

    int sendResult3 = send(
        clientSocket,
        reinterpret_cast<const char *>(&packet3),
        sizeof(packet3),
        0);

    std::cout << "send 3: " << sendResult3 << std::endl;

    // 테스트가 끝날 때까지 프로그램 유지
    std::cin.get();

    // 5. Socket 종료
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}