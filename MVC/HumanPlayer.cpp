//
// Created by mfbut on 3/9/2019.
//

#include <utility>
#include "HumanPlayer.h"
#include "ShipPlacement.h"
#include "Attack.h"

BattleShip::HumanPlayer::HumanPlayer(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : Player(
        gameAttributes, view) {

}

std::unique_ptr<BattleShip::Move> BattleShip::HumanPlayer::getMove() {
    std::pair<int,int> firingCoordinate;
    firingCoordinate=view.getFiringCoordinate(*this);
    return std::make_unique<Attack>(*this,firingCoordinate.first,firingCoordinate.second);
}

void BattleShip::HumanPlayer::initializeName() {
    name=view.getPlayerName(id);
}

void BattleShip::HumanPlayer::placeShips() {
    for(auto i=shipHealths.begin();i!=shipHealths.end();i++){
        bool valid=false;
        ShipPlacement shipPlacement=ShipPlacement();
        while (!valid){     //validation for the ship placement, check if it is in bound or no, check if it is occupied by other ship
            shipPlacement=view.getShipPlacement((*this),i->first,i->second);
            valid=board.canPlaceShipAt(shipPlacement);
        }
        board.AddShip(i->first,shipPlacement);
    }
    view.showPlacementBoardVersion2((*this));
}
