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

int Player::GetX(){
    return X;
}

int Player::GetY(){
    return Y;
}


PlayerStatus Player::GetStatus(){
    PlayerStatus status;

    status.HP = this->HP;
    status.State = this->State;

    return status;
}