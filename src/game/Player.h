#pragma once

enum class PlayerState
{
    Alive,
    Dead
};

struct PlayerStatus{
    int HP;
    PlayerState State;
};

class Player{
    public:
        Player(int id);
        void Move(int X, int Y);
        void TakeDamage(int damage);
        int GetX();
        int GetY();
        PlayerStatus GetStatus();


    private:
        int ID,
            X,
            Y,
            HP;
        PlayerState State;


};