//
// Created by mfbut on 3/9/2019.
//

#include <algorithm>
#include <vector>
#include <cctype>
#include "StandardView.h"
#include "Utility.h"

BattleShip::PlayerConfiguration BattleShip::StandardView::getPlayerConfiguration() {
    int choice=-1;
    do{
        do{
            out<<"What type of game do you want to play?"<<std::endl;
            out<<"1. Human vs Human"<<std::endl;
            out<<"2. Human vs AI"<<std::endl;
            out<<"3. AI vs AI"<<std::endl;
            out<<"Your choice: ";
            in>>choice;
            if(in.fail()){
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
            else{
                break;
            }
        }
        while(true);

    }
    while (!contains<int,std::vector<int>>(choice,{1,2,3}));
    BattleShip::PlayerConfiguration playerConfiguration(0,0);
    if(choice==1){
        playerConfiguration.numHumanPlayers=2;
        playerConfiguration.numAiPlayers=0;
    }
    else if(choice==2){
        playerConfiguration.numHumanPlayers=1;
        playerConfiguration.numAiPlayers=1;
    }
    else if(choice==3){
        playerConfiguration.numHumanPlayers=0;
        playerConfiguration.numAiPlayers=2;
    }
    return playerConfiguration;
}

BattleShip::StandardView::StandardView():in(std::cin),out(std::cout) {}

int BattleShip::StandardView::getAiChoice() {
    //TA Help
    int choice=-1;
    do{
        do{
            out<<"What AI do you want?"<<std::endl;
            out<<"1. Cheating AI"<<std::endl;
            out<<"2. Random AI"<<std::endl;
            out<<"3. Hunt Destroy AI"<<std::endl;
            out<<"Your choice: ";
            in>>choice;
            if(in.fail()){
                in.clear();
                in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            }
            else{
                break;
            }
        }
        while(true);
    }
    while (!contains<int,std::vector<int>>(choice,{1,2,3}));
    return choice;
}

void BattleShip::StandardView::showPlacementBoard(const BattleShip::Player &player) {
    //TA Help
    out<<player.getName()<<"'s Board"<<std::endl;
    printBoardAsVisible(player.getBoard());
}

std::pair<int, int> BattleShip::StandardView::getFiringCoordinate(const BattleShip::Player &attacker) {
    //TA Help
    int row,col;
    showPlayersBoard(attacker);
    do{
        out<<attacker.getName()<<", where would you like to fire?"<<std::endl;
        out<<"Enter your attack coordinate in the form row col: ";
        in>>row;
        in>>col;
        if(in.fail()){
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else{
            break;
        }
    }
    while(true);

    return {row,col};
}

void BattleShip::StandardView::printBoardAsVisible(const BattleShip::Board &board) {
    out<<"  ";
    for(int i=0;i<board.getNumCols();i++){
        out<<std::to_string(i)<<" ";
    }
    out<<std::endl;
    for(int i=0;i<board.getNumRows();i++){
        out<<std::to_string(i)<<" ";
        for(int j=0;j<board.getNumCols();j++){
            char output = board.at(i,j).getContentsIfVisible();
            out<<output<<" ";
        }
        out<<std::endl;
    }
}

void BattleShip::StandardView::printBoardAsObscured(const BattleShip::Board &board) {
    out<<"  ";
    for(int i=0;i<board.getNumCols();i++){
        out<<std::to_string(i)<<" ";
    }
    out<<std::endl;
    for(int i=0;i<board.getNumRows();i++){
        out<<std::to_string(i)<<" ";
        for(int j=0;j<board.getNumCols();j++){
            char output = board.at(i,j).getContentsIfHidden();
            out<<output<<" ";
        }
        out<<std::endl;
    }
}

ShipPlacement BattleShip::StandardView::getShipPlacement(const BattleShip::Player &player, char shipChar, int shipLen) {
    printBoardAsVisible(player.getBoard());
    char choice=' ';
    do{
        out<<player.getName()<<", do you want to place "<<shipChar<<" horizontally or vertically?"<<std::endl;
        out<<"Enter h for horizontal or v for vertical"<<std::endl;
        out<<"Your choice: ";
        verifiedRead(in,choice);
    }
    while (!contains<char,std::vector<char>>(choice,{'h','v'}));
    int row,col;
    int finalrow,finalcol;
    do{
        out<<player.getName()<<", enter the row and column you want to place "<<shipChar<<", which is "<<std::to_string(shipLen)<<" long, at with a space in between row and col: ";
        in>>row;
        in>>col;
        if(in.fail()){
            in.clear();
            in.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        }
        else{
            break;
        }
    }
    while(true);
    if(choice=='h'){
        finalrow=row;
        finalcol=col+shipLen-1;
    }
    else{
        finalrow=row+shipLen-1;
        finalcol=col;
    }
    return ShipPlacement(row,col,finalrow,finalcol);
}

std::string BattleShip::StandardView::getPlayerName(int i) {
    std::string name;
    out<<"Player "<<i<<" please enter your name: ";
    verifiedRead(in,name);
    return name;
}

void BattleShip::StandardView::updateShipPlacementView(const BattleShip::Player &player) {
    printBoardAsVisible(player.getBoard());
}

void BattleShip::StandardView::showWinner(const BattleShip::Player &winner) {
    out<<winner.getName()<<" won the game!";
}

void BattleShip::StandardView::showResultOfAttack(const BattleShip::Player &attacker,
                                                  const BattleShip::AttackResult &attackResult) {
    showPlayersBoard(attacker);
    if(attackResult.hit||attackResult.destroyed){
        if(attackResult.hit){
            out<<attacker.getName()<<" hit "<<attacker.getOpponent().getName()<<"'s "<<attackResult.shipChar<<"!"<<std::endl;
        }
        if(attackResult.destroyed){
            out<<attacker.getName()<<" destroyed "<<attacker.getOpponent().getName()<<"'s "<<attackResult.shipChar<<"!"<<std::endl;
        }
        out<<std::endl;
    }
    else{
        out<<"Missed."<<std::endl;
        out<<std::endl;
    }
}

void BattleShip::StandardView::showPlayersBoard(const BattleShip::Player &player) {
    out<<player.getName()<<"'s Firing Board"<<std::endl;
    printBoardAsObscured(player.getOpponent().getBoard());
    out<<std::endl<<std::endl;
    out<<player.getName()<<"'s Placement Board"<<std::endl;
    printBoardAsVisible(player.getBoard());
}

void BattleShip::StandardView::showPlacementBoardVersion2(const BattleShip::Player &player) {
    printBoardAsVisible(player.getBoard());
}

