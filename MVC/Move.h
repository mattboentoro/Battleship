//
// Created by mfbut on 3/9/2019.
//

#ifndef BATTLESHIP_MOVE_H
#define BATTLESHIP_MOVE_H
#include "Player.h"
#include "Model.h"
#include "View.h"

namespace BattleShip {
class Player;
class AiPlayer;
class HumanPlayer;
class Model;
class View;

class Move {
 public:
  Move(Player& moveMaker);
  virtual void enact(Model& model, View& view) = 0;
  virtual void enact(Player& player, View& view) = 0;
  virtual bool preenacthit(Player& player) = 0;
  virtual bool isValid() const = 0;
  int getRow();
  int getCol();
  void setRow(int row);
  void setCol(int col);

 protected:
  Player& moveMaker;
  int row;
  int col;
};
}

#endif //BATTLESHIP_MOVE_H
