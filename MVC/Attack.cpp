//
// Created by mfbut on 3/10/2019.
//

#include "Attack.h"

BattleShip::Attack::Attack(BattleShip::Player &attacker, int row, int col):Move(attacker){
    this->row=row;
    this->col=col;
}

bool BattleShip::Attack::isValid() const {
    if(!moveMaker.getOpponent().getBoard().inBounds(row,col)){
        return false;
    }
    else if(moveMaker.getOpponent().getBoard().at(row,col).HasBeenFiredAt()){
        return false;
    }
    return true;
}

void BattleShip::Attack::enact(BattleShip::Player &player, BattleShip::View &view) {
    if(player.getBoard().at(row,col).containsShip()){
        char shipMarker=player.getBoard().at(row,col).getContents();
        player.shipHealths[shipMarker]--;
        player.getBoard().at(row,col).setContents(player.getBoard().at(row,col).getHitMarker());

    }
    else{
        player.getBoard().at(row,col).setContents(player.getBoard().at(row,col).getMissMarker());
    }
    player.getBoard().at(row,col).setHasBeenFiredAt(true);
}

void BattleShip::Attack::enact(BattleShip::Model &model, BattleShip::View &view) {
    if(model.getDefendingPlayer().getBoard().at(row,col).containsShip()){
        model.getDefendingPlayer().getBoard().at(row,col).setContents(model.getDefendingPlayer().getBoard().at(row,col).getHitMarker());
    }
    else{
        model.getDefendingPlayer().getBoard().at(row,col).setContents(model.getDefendingPlayer().getBoard().at(row,col).getMissMarker());
    }
    model.getDefendingPlayer().getBoard().at(row,col).setHasBeenFiredAt(true);
}

bool BattleShip::Attack::preenacthit(BattleShip::Player &player) {
    return player.getBoard().at(row,col).containsShip();
}
