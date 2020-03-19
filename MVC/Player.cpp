//
// Created by mfbut on 3/9/2019.
//

#include "Player.h"
#include "Attack.h"

int BattleShip::Player::num_instances = 1;

void BattleShip::Player::setName(const std::string &name) {
    this->name=name;
}

const std::string &BattleShip::Player::getName() const {
    return name;
}

const int BattleShip::Player::getId() const {
    return id;
}

const BattleShip::Board &BattleShip::Player::getBoard() const {
    return board;
}

BattleShip::Board &BattleShip::Player::getBoard() {
    return board;
}

BattleShip::Player &BattleShip::Player::getOpponent() {
    //TA Help
    return *opponent;
}

const BattleShip::Player &BattleShip::Player::getOpponent() const {
    //TA Help
    return const_cast<Player*>(this)->getOpponent();
}

void BattleShip::Player::setOpponent(BattleShip::Player &opponent) {
    //TA Help
    this->opponent=&opponent;
}

BattleShip::Player::Player(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view):shipHealths(gameAttributes.getShipAttributes()),id(num_instances),view(view),board(gameAttributes.getNumRows(),gameAttributes.getNumCols()) {
++num_instances;

}

BattleShip::AttackResult BattleShip::Player::fireAt(int row, int col) {
    std::map<char, int> previousAttackHealth = getOpponent().shipHealths;
    std::map<char,int>::iterator previousIterator = previousAttackHealth.begin();
    Attack attack(*this, row, col);
    attack.enact((*this).getOpponent(), view);
    std::map<char,int>::iterator currentIterator=getOpponent().shipHealths.begin();
    while(currentIterator!=getOpponent().shipHealths.end() && previousIterator!=previousAttackHealth.end()){
        if((*currentIterator).second!=(*previousIterator).second){
            if((*currentIterator).second == 0){
                return AttackResult(true, true, (*currentIterator).first);
            } else {
                return AttackResult(true, false, (*currentIterator).first);
            }
        }
        currentIterator++;
        previousIterator++;
    }
    return AttackResult(false, false, '*');
}

bool BattleShip::Player::allShipsSunk() const {
    for(auto i=shipHealths.begin();i!=shipHealths.end();i++){
        if((*i).second!=0){
            return false;
        }
    }
    return true;
}

