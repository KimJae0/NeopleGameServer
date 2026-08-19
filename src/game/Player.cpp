#include "Player.h"

Player::Player(int id){
    ID = id;
    X = 0;
    Y = 0;
    HP = 100;
    State = PlayerState::Alive;

}

void Player::Move(int X, int Y){
    this->X = X;
    this->Y = Y;
}

void Player::TakeDamage(int damage){
    
    
    HP -= damage;

    if(HP <= 0){
        HP = 0;
        State = PlayerState::Dead;
    }
}

int Player::GetID() const{
    return ID;
}

int Player::GetX() const{
    return X;
}

int Player::GetY() const{
    return Y;
}


PlayerStatus Player::GetStatus() const{
    PlayerStatus status;

    status.HP = this->HP;
    status.State = this->State;

    return status;
}

void Player::SetStatus(int x, int y, int hp, PlayerState state){
    this->X = x;
    this->Y = y;
    this->HP = hp;
    this->State = state;

}