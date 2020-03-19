//
// Created by mfbut on 3/9/2019.
//

#include <stdexcept>
#include <vector>
#include <sstream>
#include "PlayerConfiguration.h"
#include "Controller.h"
#include "HumanPlayer.h"
#include "AiPlayer.h"
#include "StandardView.h"
#include "CheatingAI.h"
#include "RandomAI.h"
#include "HuntDestroyAI.h"
#include "Utility.h"

void BattleShip::Controller::setupGame(const std::string &GameConfigurationFile) {
    model.loadGameConfigurationFromFile(GameConfigurationFile);
    setupGame();
}

void BattleShip::Controller::setupGame(const std::string &GameConfigurationFile, int seed) {
    BattleShip::AiPlayer::seed_random_number_generator(seed);
    setupGame(GameConfigurationFile);
}

void BattleShip::Controller::setupGame() {
    PlayerConfiguration playerConfiguration=view.get()->getPlayerConfiguration();
    for(int i=0;i<playerConfiguration.numHumanPlayers;i++){
        model.addPlayer<HumanPlayer>(*view.get());
    }
    for(int j=0;j<playerConfiguration.numAiPlayers;j++){
        int choice=view.get()->getAiChoice();
        if(choice==1){
            model.addPlayer<CheatingAI>(*view.get());
        }
        else if(choice==2){
            model.addPlayer<RandomAI>(*view.get());
        }
        else if(choice==3){
            model.addPlayer<HuntDestroyAI>(*view.get());
        }
    }
    model.SetOpponents();
    hasBeenSetUp=true;
}

BattleShip::Controller::Controller():hasBeenSetUp(false),model(),view(std::make_unique<StandardView>()) {}

void BattleShip::Controller::playGame() {
    while (!model.isGameOver()){
        Player& attacker=model.getAttackingPlayer();
        bool valid=false;
        std::unique_ptr<Move> move;
        while(!valid){      //validation that the move is inbound or has not been fired before
            move=attacker.getMove();
            valid=move.get()->isValid();
        }
        AttackResult result=attacker.fireAt(move.get()->getRow(),move.get()->getCol());
        view.get()->showResultOfAttack(attacker,result);
        model.changeTurn();
    }
    model.endGame();
    view.get()->showWinner(model.getWinner());
}
