//
// Created by mfbut on 3/11/2019.
//

#include "RandomAI.h"
#include "Attack.h"
#include "Utility.h"

BattleShip::RandomAI::RandomAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view) : AiPlayer(
        gameAttributes, view) {
    for(int i=0;i<gameAttributes.getNumRows();i++){
        for(int j=0;j<gameAttributes.getNumCols();j++){
            firingLocations.push_back(std::pair<int,int>(i,j));
        }
    }
}

std::unique_ptr<BattleShip::Move> BattleShip::RandomAI::getMove() {
    std::pair<int,int> random=*chooseRandom(firingLocations,randomNumberGenerator);
    firingLocations.erase(std::remove(firingLocations.begin(),firingLocations.end(),random),firingLocations.end());
    return std::unique_ptr<BattleShip::Move>(new Attack(*this,random.first,random.second));
}
