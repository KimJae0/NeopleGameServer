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
        int GetID() const;
        int GetX() const;
        int GetY() const;
        PlayerStatus GetStatus() const;
        void SetStatus(int x, int y, int hp, PlayerState state);


    private:
        int ID,
            X,
            Y,
            HP;
        PlayerState State;


};