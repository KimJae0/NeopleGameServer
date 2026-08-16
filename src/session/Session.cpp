#include "Session.h"


Session::Session(){
    playerId = 0;
}


void Session::ConnectPlayer(int id){
    playerId = id;
}


int Session::GetPlayerId(){
    return playerId;
}