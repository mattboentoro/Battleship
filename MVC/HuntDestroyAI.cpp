//
// Created by mfbut on 3/11/2019.
//

#include <algorithm>
#include "HuntDestroyAI.h"
#include "Attack.h"
#include "Utility.h"

std::vector<std::pair<int, int>>
BattleShip::HuntDestroyAI::getSurroundingLocations(const std::pair<int, int> &center) const {
    std::vector<std::pair<int,int>> surroundingLocations;
    if(check(center.first,center.second-1)){
        if(secondarycheck(center.first,center.second-1)){
            surroundingLocations.push_back({center.first,center.second-1}); //left
        }
    }
    if(check(center.first-1,center.second)){
        if(secondarycheck(center.first-1,center.second)){
            surroundingLocations.push_back({center.first-1,center.second}); //up
        }
    }
    if(check(center.first,center.second+1)){
        if(secondarycheck(center.first,center.second+1)){
            surroundingLocations.push_back({center.first,center.second+1}); //right
        }
    }
    if(check(center.first+1,center.second)){
        if(secondarycheck(center.first+1,center.second)){
            surroundingLocations.push_back({center.first+1,center.second}); //down
        }
    }
    return surroundingLocations;
}

std::unique_ptr<BattleShip::Move> BattleShip::HuntDestroyAI::getMove() {
    if(priorityFiringQueue.empty()){
        auto itr = chooseRandom(firingLocations,randomNumberGenerator);
        std::pair<int,int> point=*itr;
        if(itr == firingLocations.end()){
            std::cout << "Terrible News" <<std::endl;
        }
        firingLocations.erase(itr);
        std::unique_ptr<BattleShip::Move> move(new Attack(*this,point.first,point.second));
        if(move.get()->preenacthit(this->getOpponent())){
            std::pair<int,int>pts(move.get()->getRow(),move.get()->getCol());
            destroymode=true;
            for(auto const& val:getSurroundingLocations(pts)){
                priorityFiringQueue.push_back(val);
            }

        }

        return move;
    }
    else{
        std::pair<int,int>point=priorityFiringQueue.front();
        priorityFiringQueue.erase(priorityFiringQueue.begin());
        firingLocations.erase(std::remove(firingLocations.begin(),firingLocations.end(),point),firingLocations.end());
        std::unique_ptr<BattleShip::Move>move(new Attack(*this,point.first,point.second));
        if(move.get()->preenacthit(this->getOpponent())){
            destroymode=true;
            for(auto const& val:getSurroundingLocations(point)){
                priorityFiringQueue.push_back(val);
            }

        }

        return move;
    }


}

BattleShip::HuntDestroyAI::HuntDestroyAI(const BattleShip::GameAttributes &gameAttributes, BattleShip::View &view)
        : RandomAI(gameAttributes, view),destroymode(false) {}


bool BattleShip::HuntDestroyAI::check(int row, int col)const {
    return opponent->getBoard().inBounds(row,col);
}

bool BattleShip::HuntDestroyAI::secondarycheck(int row, int col) const {
    return (!opponent->getBoard().at(row,col).HasBeenFiredAt());
}
