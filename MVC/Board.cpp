//
// Created by mfbut on 3/10/2019.
//

#include "Board.h"

int BattleShip::Board::getNumRows() const {
    return num_row;
}

int BattleShip::Board::getNumCols() const {
    return num_col;
}

BattleShip::Cell &BattleShip::Board::at(int i, int j) {
    return boardState[i][j];
}

const BattleShip::Cell &BattleShip::Board::at(int i, int j) const {
    return boardState[i][j];
}

void BattleShip::Board::AddShip(char shipChar, const ShipPlacement &shipPlacement) {
    for(int i=shipPlacement.rowStart;i<shipPlacement.rowEnd+1;i++){
        for(int j=shipPlacement.colStart;j<shipPlacement.colEnd+1;j++){
            boardState[i][j].setContents(shipChar);
        }
    }
}

bool BattleShip::Board::inBounds(int row, int col) const {
    if(row>=num_row||col>=num_col||row<0||col<0){
        return false;
    }
    return true;
}

bool BattleShip::Board::canPlaceShipAt(const ShipPlacement &shipPlacement) const {
    return (inBounds(shipPlacement)&&spacesAreEmpty(shipPlacement));
}

BattleShip::Board::Board(int numRows, int numCols): num_row(numRows),num_col(numCols),blankChar('*') {
    for(int i=0;i<numRows;i++){
        std::vector<Cell>tempvec;
        for(int j=0;j<numCols;j++){
            Cell temp=Cell('*');
            tempvec.push_back(temp);
        }
        boardState.push_back(tempvec);
    }
}

bool BattleShip::Board::inBounds(const ShipPlacement &shipPlacement) const {
    int startrow=shipPlacement.rowStart;
    int endrow=shipPlacement.rowEnd;
    int startcol=shipPlacement.colStart;
    int endcol=shipPlacement.colEnd;
    bool result=true;
    for(int i=startrow;i<=endrow;i++){
        for(int j=startcol;j<=endcol;j++){
            if(!inBounds(i,j)){
                result=false;
            }
        }
    }
    return result;
}

bool BattleShip::Board::spacesAreEmpty(const ShipPlacement &shipPlacement) const {
    int startrow=shipPlacement.rowStart;
    int endrow=shipPlacement.rowEnd;
    int startcol=shipPlacement.colStart;
    int endcol=shipPlacement.colEnd;
    bool result=true;
    for(int i=startrow;i<=endrow;i++){
        for(int j=startcol;j<=endcol;j++){
            if(boardState[i][j].getContents()!='*'){
                result=false;
            }
        }
    }
    return result;
}
