#include "Database.h"
#include <iostream>

bool Database::Connect()
{
    try
    {
        session = new mysqlx::Session(
            "127.0.0.1",
            33060,
            "root",
            "1234",
            "neoplegameserver");

        return true;
    }
    catch (const mysqlx::Error &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool Database::LoadPlayer(int id, Player &player)
{

    try
    {

        mysqlx::SqlResult result = session->sql(R"(
            SELECT ID, X, Y, HP, State
            FROM players
            WHERE ID = ?
        )").bind(id).execute();


        mysqlx::Row row = result.fetchOne();
        if(row.isNull()){
            return false;
        }

    

        int X = row[1].get<int>();
        int Y = row[2].get<int>();
        int HP = row[3].get<int>();
        PlayerState State = static_cast<PlayerState>(row[4].get<int>());

        player.SetStatus(X, Y, HP, State);
    

        return true;
    }
    catch (const mysqlx::Error &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}

bool Database::SavePlayer(const Player &player)
{
    try
    {
        int ID = player.GetID();
        int X = player.GetX();
        int Y = player.GetY();

        PlayerStatus status = player.GetStatus();
        int HP = status.HP;
        int State = static_cast<int>(status.State);

        session->sql(R"(
            UPDATE players
            SET X = ?,
                Y = ?,
                HP = ?,
                State = ?
            WHERE ID = ?
        )").bind(X, Y, HP, State, ID).execute();

        return true;
    }
    catch (const mysqlx::Error &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}


bool Database::SavePlayer(const Task& task){
    try
    {
        int ID = task.id;
        int X = task.x;
        int Y = task.y;
        int HP = task.HP;
        int State = static_cast<int>(task.State);

        session->sql(R"(
            UPDATE players
            SET X = ?,
                Y = ?,
                HP = ?,
                State = ?
            WHERE ID = ?
        )").bind(X, Y, HP, State, ID).execute();

        return true;
    }
    catch (const mysqlx::Error &e)
    {
        std::cout << e.what() << std::endl;
        return false;
    }
}