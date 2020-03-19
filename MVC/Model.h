//
// Created by mfbut on 3/9/2019.
//

#ifndef BATTLESHIP_MODEL_H
#define BATTLESHIP_MODEL_H


#include <vector>
#include <memory>
#include "View.h"
#include "Player.h"
#include "GameAttributes.h"
namespace BattleShip {
class Move;
class Player;
class View;
class Model {

 public:
  Model();
  Player& getAttackingPlayer();

  Player& getDefendingPlayer();

  bool isGameOver() const;
  void changeTurn();
  void loadGameConfigurationFromFile(const std::string& gameConfigurationFile);
  template <typename PlayerType>
  void addPlayer(View& view) {
    std::unique_ptr<PlayerType> player = std::make_unique<PlayerType>(gameAttributes, view);
    player->initializeName();
    player->placeShips();
    players.push_back(std::move(player));
  }

    void endGame();

  Player& getWinner();

  void SetOpponents();
 protected:
  GameAttributes gameAttributes;
  std::vector<std::unique_ptr<Player>> players;
  int playerTurn;
  bool forcedGameOver;
};

}
#endif //BATTLESHIP_MODEL_H
