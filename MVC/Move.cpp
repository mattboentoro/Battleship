//
// Created by mfbut on 3/9/2019.
//

#include "Move.h"

BattleShip::Move::Move(BattleShip::Player& moveMaker) : moveMaker(moveMaker),row(0),col(0) {}

int BattleShip::Move::getRow() {
    return row;
}

int BattleShip::Move::getCol() {
    return col;
}

void BattleShip::Move::setRow(int row) {
    this->row=row;
}

void BattleShip::Move::setCol(int col) {
    this->col=col;
}
