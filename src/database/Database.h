#pragma once

#include "Player.h"
#include <mysqlx/xdevapi.h>

class Database{


    public:
        bool Connect();
        bool LoadPlayer(int id, Player& player);
        bool SavePlayer(const Player& player);


    private:
        mysqlx::Session* session = nullptr;

};