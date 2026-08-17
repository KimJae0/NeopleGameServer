#include "Session.h"
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


std::string Session::Receive(){
    std::vector<char> buffer(1024);

    int result = recv(
        ClientSocket,
        buffer.data(),
        buffer.size(),
        0
    );

    std::string temp(buffer.data(), result);

    return temp;


}