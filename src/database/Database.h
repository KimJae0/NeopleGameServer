#pragma once

#include "Player.h"
#include "TaskQueue.h"
#include <mysqlx/xdevapi.h>

class Database{


    public:
        bool Connect();
        bool LoadPlayer(int id, Player& player);
        bool SavePlayer(const Player& player);
        bool SavePlayer(const Task& task);


    private:
        mysqlx::Session* session = nullptr;

};