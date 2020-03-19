//
// Created by mfbut on 3/9/2019.
//
#include <utility>
#include "Utility.h"
#include "GameAttributes.h"

BattleShip::GameAttributes::GameAttributes(int numRows, int numCols):numRows(numRows),numCols(numCols) {

}

int BattleShip::GameAttributes::getNumRows() const {
    return numRows;
}

int BattleShip::GameAttributes::getNumCols() const {
    return numCols;
}

const std::map<char, int> &BattleShip::GameAttributes::getShipAttributes() const {
    return shipAttributes;
}

void BattleShip::GameAttributes::addShip(char ShipChar, int ShipSize) {
    shipAttributes[ShipChar]=ShipSize;
}

int BattleShip::GameAttributes::getShipSize(const char ShipChar) const {
    return shipAttributes.at(ShipChar);
}

