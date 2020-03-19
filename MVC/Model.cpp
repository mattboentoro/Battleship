//
// Created by mfbut on 3/9/2019.
//

#include <fstream>
#include <algorithm>
#include "Model.h"

BattleShip::Model::Model():playerTurn(0),forcedGameOver(false) {}

BattleShip::Player &BattleShip::Model::getAttackingPlayer() {
    return *players.at(playerTurn).get();
}

BattleShip::Player &BattleShip::Model::getDefendingPlayer() {
    if(playerTurn==0){
        return *players.at(1).get();
    }
    return *players.at(0).get();
}

bool BattleShip::Model::isGameOver() const {
    return players.at(0).get()->allShipsSunk() || players.at(1).get()->allShipsSunk();
}

void BattleShip::Model::changeTurn() {
    if(playerTurn==0){
        playerTurn=1;
    }
    else{
        playerTurn=0;
    }
}

void BattleShip::Model::loadGameConfigurationFromFile(const std::string &gameConfigurationFile) {
    std::ifstream myfile;
    myfile.open(gameConfigurationFile);
    int numrow,numcol,numship,currentshipvalue;
    char currentshipchar;
    myfile>>numrow;
    myfile>>numcol;
    myfile>>numship;
    gameAttributes=GameAttributes(numrow,numcol);
    for(int i=0;i<numship+1;i++){
        myfile>>currentshipchar;
        myfile>>currentshipvalue;
        gameAttributes.addShip(currentshipchar,currentshipvalue);
    }
    myfile.close();
}

void BattleShip::Model::endGame() {
    forcedGameOver= true;
}

BattleShip::Player &BattleShip::Model::getWinner() {
    changeTurn();
    return *players.at(playerTurn).get();
}

void BattleShip::Model::SetOpponents() {
    players.at(0).get()->setOpponent(*players.at(1).get());
    players.at(1).get()->setOpponent(*players.at(0).get());
}
