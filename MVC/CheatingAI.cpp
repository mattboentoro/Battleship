//
// Created by mfbut on 3/11/2019.
//
#include <stdexcept>
#include "CheatingAI.h"
#include "Attack.h"

BattleShip::CheatingAI::CheatingAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : AiPlayer(
        gameAttributes, view),firstTime(true),numRow(gameAttributes.getNumRows()),numCol(gameAttributes.getNumCols()) {
}

std::unique_ptr<BattleShip::Move> BattleShip::CheatingAI::getMove() {
    if(firstTime== true){
        for(int i=0;i<numRow;i++){
            for(int j=0;j<numCol;j++){
                if((*this).getOpponent().getBoard().at(i,j).getContents()!='*'){
                    firingLocations.push_back(std::pair<int,int>(i,j));
                }
            }
        }
        firstTime= false;
    }
    int fireRow=firingLocations[0].first;
    int fireCol=firingLocations[0].second;
    firingLocations.erase(firingLocations.begin());
    std::unique_ptr<BattleShip::Move> move(new Attack(*this,fireRow,fireCol));
    return move;
}
