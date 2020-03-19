//
// Created by mfbut on 3/10/2019.
//

#ifndef BATTLESHIP_BOARD_H
#define BATTLESHIP_BOARD_H
#include <string>
#include <vector>
#include "ShipPlacement.h"
#include "Cell.h"

namespace BattleShip {
class Board {
 public:
  Board(int numRows, int numCols);
  bool canPlaceShipAt(const ShipPlacement& shipPlacement) const;

  int getNumRows() const;
  int getNumCols() const;

  void AddShip(char shipChar, const ShipPlacement& shipPlacement);
  bool inBounds(int row, int col) const;

  Cell& at(int i, int j);
  const Cell& at(int i, int j) const;


 protected:
  bool inBounds(const ShipPlacement& shipPlacement) const;
  bool spacesAreEmpty(const ShipPlacement& shipPlacement) const;

  //members

  const int num_row;
  const int num_col;
  const char blankChar;
  std::vector<std::vector<Cell>> boardState;
};
}

#endif //BATTLESHIP_BOARD_H
